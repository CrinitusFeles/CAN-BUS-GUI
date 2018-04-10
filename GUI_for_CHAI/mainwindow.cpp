#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphplotwindow.h"
#include "settingswindow.h"
#include <QCoreApplication>

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <chai.h>
#ifdef WIN32
#include <windows.h>
#include <process.h>
#endif

#define CM_RCVBUF_SIZE 64

const char cm_version[] = "CAN monitor for CHAI, ver. 3.2, 01 Sep 2016";

_u8 chan;
int baud;
_u8 bt0, bt1;


int channelForm = -1;
int baudrateForm = -1;
int maskForm = 0;
bool listenmodeForm = false;

double l0[3] = {14990.0, 15024.0, 14972.0};
double l1[3] = {56007.0, 56011.0, 56012.0};
double l2[3] = {25000.0, 25000.0, 25000.0};

typedef struct {
    unsigned char  uls_xx[3][12];
    unsigned char  uls_xx_n[3];
    unsigned char  error_code[3];
}TO_HOST;
TO_HOST to_host;


bool isConnected = false;

void MainWindow::printMassege(canmsg_t *msg){
    ui->textEdit->insertPlainText("\nTX ID: 0x" + QString::number(msg->id, 16) + "    Length: " + QString::number(msg->len));
    for(int j = 0; j < msg->len; j++){
        ui->textEdit->insertPlainText("    # 0x" + QString::number(msg->data[j], 16));
    }
}

float MainWindow::Fira(unsigned char *xx){
    unsigned char nk0,nk1,vk0,vk1;
    int rez1,rez2;
    float result;
    nk0=xx[0];//TdcRead(TDC_ERG_REG0); //Lower byte xxxx.xxXX - internal address counter select lsb/msb next register ets...
    nk1=xx[1];//TdcRead(TDC_ERG_REG0); //Higher byte xxxx.XXxx
    vk0=xx[2];//TdcRead(TDC_ERG_REG0); //Lower byte xxXX.xxxx
    vk1=xx[3];//TdcRead(TDC_ERG_REG0); //Higher byte XXxx.xxxx
    rez1=vk0|(int)vk1<<8; //XXXX.xxxx
    rez2=nk0|(int)nk1<<8; //xxxx.XXXX
    result = 50.0*((float)(rez1)+(float)(rez2)/65536.0);
return result;
}

int MainWindow::binfo(void)
{
    _s16 i, j, ret;
    canboard_t binfo;
    int cnt = 0;
    _u32 fwver = 0;
    char serialbuf[256];

    for (i = 0; i < CI_BRD_NUMS; i++) {
        binfo.brdnum = (_u8) i;
        ret = CiBoardInfo(&binfo);
        if (ret < 0)
            continue;


        ui->textEdit->insertPlainText(binfo.name); //для вывода массива символов

        if (CiBoardGetSerial(binfo.brdnum, serialbuf, 256) >= 0) { // board has serial number
            serialbuf[255] = '\0';
            //printf(", serial %s", serialbuf);
            ui->textEdit->insertPlainText("   serial ");
            ui->textEdit->insertPlainText(serialbuf);
        }
        //printf("]\n");

        for (j = 0; j < 4; j++) {
            if (binfo.chip[j] >= 0) {
                ui->textEdit->insertPlainText("   channel ");
                ui->textEdit->insertPlainText(QString::number(binfo.chip[j]));
                //printf("   channel %d", binfo.chip[j]);
                if ( CiOpen( (_u8) binfo.chip[j], 0 ) >= 0) {
                    ui->listWidget->currentItem()->setText(ui->listWidget->currentItem()->text()+" free");
                    //printf("     (free");
                    CiGetFirmwareVer( (_u8) binfo.chip[j], &fwver);
                    if(fwver > 0)
                        //printf(", firmware %d.%d", VERMIN(fwver), VERSUB(fwver));
                    CiClose( (_u8) binfo.chip[j]);
                    //printf(")");
                } else {
                    ui->listWidget->currentItem()->setText(ui->listWidget->currentItem()->text()+" busy");
                    //printf("     (busy)");
                }
                cnt++;
            }
        }

    }
    return cnt;
}

void MainWindow::get_chan(void)
{
    ui->textEdit->append("CAN adapters:");
    if (binfo() > 0) {
        ui->textEdit->append("CAN channel to use =>" + QString::number(channelForm));
        //printf("\nCAN channel to use => ");
        //scanf(" %i", &ch);
        chan = (_u8) channelForm;
    } else {

        ui->textEdit->append("\nThere are no CAN channels.\nCheck CHAI installation.\n\n");
        ui->textEdit->append("press [Enter] key to quit...");
        //fgetc(stdin);
       // exit(1);
    }
}

void MainWindow::get_bitrate(void)
{
    baud = baudrateForm;
    switch (baud) {
    case 1000:
        bt0 = BCI_1M_bt0;
        bt1 = BCI_1M_bt1;
        break;
    case 800:
        bt0 = BCI_800K_bt0;
        bt1 = BCI_800K_bt1;
        break;
    case 500:
        bt0 = BCI_500K_bt0;
        bt1 = BCI_500K_bt1;
        break;
    case 250:
        bt0 = BCI_250K_bt0;
        bt1 = BCI_250K_bt1;
        break;
    case 125:
        bt0 = BCI_125K_bt0;
        bt1 = BCI_125K_bt1;
        break;
    case 100:
        bt0 = BCI_100K_bt0;
        bt1 = BCI_100K_bt1;
        break;
    case 50:
        bt0 = BCI_50K_bt0;
        bt1 = BCI_50K_bt1;
        break;
    case 20:
        bt0 = BCI_20K_bt0;
        bt1 = BCI_20K_bt1;
        break;
    case 10:
        bt0 = BCI_10K_bt0;
        bt1 = BCI_10K_bt1;
        break;
        ////////////We don't use manual bit rate //////////
    default:
        ui->textEdit->append("Unsupported bit rate, valid only:\n 1000, 800, 500, 250, 125, 100, 50, 20, 10, 0 (for manual bit timing)\n");

        break;
    }
}


void MainWindow::init_can_channel(void)
{
    _s16 ret;
    ui->textEdit->append("chan = "+QString::number(chan));
    if ((ret = CiOpen(chan, CIO_CAN11 | CIO_CAN29)) < 0) {
        QMessageBox::critical(this, "Warning", "Error opening CAN channel");
        //fprintf(stdout, "Error opening CAN channel %d, ret = %d\n", chan, ret);

        //exit(1); //вернуть
    }

    if ((ret = CiSetBaud(chan, bt0, bt1)) < 0) {
        QMessageBox::critical(this, "Warning", "can't set baud");
        //fprintf(stdout, "can't set baud, ret = %d\n", ret);

        //exit(1); //вернуть
    }

    if ((ret = CiSetFilter(chan, 0xffff, 0x0)) < 0) {
        QMessageBox::critical(this, "Warning", "can't set hardware filter");
        //fprintf(stdout, "can't set hardware filter, ret = %d\n", ret);

       // exit(1); //вернуть
    }
}

void MainWindow::Read(){
    canwait_t cw;
    cw.chan = chan;
    cw.wflags = CI_WAIT_RC | CI_WAIT_ER;

    canmsg_t rx[CM_RCVBUF_SIZE]; //массив структур (CM_RCVBUF_SIZE = 64)
    int ret = 0;
    int frames = 0;
    static unsigned char *ptr=0;

    ret = CiWaitEvent(&cw, 1, 1500); // timeout = 1000 миллисекунд
    if (ret > 0)
    {
        if (cw.rflags & CI_WAIT_RC) // получен кадр в канале cw.chan
        {
            frames = (int) CiRead(chan, rx, CM_RCVBUF_SIZE); //забирает из канала 64 кадра и кладет их в rx. Возвращает кол-во кадров
            //ui->textEdit->append("Some got");
            if (frames > 0)
            {
                for (int i = 0; i < frames; i++)
                {
                    ui->textEdit->insertPlainText("\nRX id: " + QString::number(rx[i].id, 16));

                    for(int j = 0; j < rx[i].len; j++)
                    {
                        ui->textEdit->insertPlainText("  # 0x" + QString::number(rx[i].data[j], 16));
                    }

                    switch (rx[i].data[0]) {
                    case 0x10:
                        ptr=(unsigned char*)&to_host;
                    case 0x11:
                    case 0x12:
                    case 0x13:
                    case 0x14:
                    case 0x15:
                        if(ptr==0)break;

                        memcpy(ptr, &rx[i].data[1], 7);
                        ptr+=7;

                        if(rx[i].data[0]==0x15){
                            float T1, T2, T3, L, L0;
                            for(int n = 0; n < 3; n++){
                                T1=Fira(&to_host.uls_xx[n][0]);
                                T2=Fira(&to_host.uls_xx[n][4]);
                                T3=Fira(&to_host.uls_xx[n][8]);
                                L0 = l0[n] * (T3 - T2) / (T2 - T1);
                                L = l1[n] - L0 - l2[n];
                                ui->TimesDisplay->append("S"+QString::number(n)+" T1 = " + QString::number(T1) +
                                                         "   T2 = " + QString::number(T2)+"   T3 = " + QString::number(T3) +
                                                         "   L = " + QString::number(L));
                                if(n==0){
                                    ui->lineEdit11->setText(QString::number(T1));
                                    ui->lineEdit12->setText(QString::number(T2));
                                    ui->lineEdit13->setText(QString::number(T3));
                                    ui->lineEdit_L1->setText(QString::number(L));
                                }
                                if(n==1){
                                    ui->lineEdit21->setText(QString::number(T1));
                                    ui->lineEdit22->setText(QString::number(T2));
                                    ui->lineEdit23->setText(QString::number(T3));
                                    ui->lineEdit_L2->setText(QString::number(L));
                                }
                                if(n==2){
                                    ui->lineEdit31->setText(QString::number(T1));
                                    ui->lineEdit32->setText(QString::number(T2));
                                    ui->lineEdit33->setText(QString::number(T3));
                                    ui->lineEdit_L3->setText(QString::number(L));
                                }
                            }
                        }
                        break;
                    case 0xBA:

                        break;
                    default:
                        break;
                    }
                }
            }
            else if (frames < 0)
            {
                ui->textEdit->append( "CiRead failed, frames = " + QString::number(frames));
            }
            else ui->textEdit->append("frames = " + QString::number(frames));

            if (cw.rflags & CI_WAIT_ER) // в канале cw[i].chan произошла ошибка
            {
                 ui->textEdit->append("flags error");
            }
        }
    }
    else if (ret < 0) {     // ошибка CiWaitEvent()
        ui->textEdit->append("CiWaitEvent() failed, ret =" + QString::number(ret));
    }
    else { // ret == 0    // timeout
        ui->textEdit->append("timeout");
    }
}



void MainWindow::slotSingleTrans(){
    if(ui->ListenModBox->isChecked()){
        GetTime();
        singleRead->start(3500);
    }
    else if(!(ui->ListenModBox->isChecked())){
        ui->label_5->setText("stopped");
    }

}
void MainWindow::slotSingleRead(){
    if(ui->ListenModBox->isChecked()){
        Read();
        singleTrans->start();
    }
    else if(!(ui->ListenModBox->isChecked())){
        ui->label_5->setText("stopped");
    }

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GraphWindow = new GraphPlotWindow;
    connect(GraphWindow, &GraphPlotWindow::openWindow, this, &MainWindow::show);


    connect(this, SIGNAL(S1T1_Changed(const QString)), GraphWindow, SLOT(getS1T1(QString)));
    connect(this, SIGNAL(S1T2_Changed(const QString)), GraphWindow, SLOT(getS1T2(QString)));
    connect(this, SIGNAL(S1T3_Changed(const QString)), GraphWindow, SLOT(getS1T3(QString)));

    connect(this, SIGNAL(S2T1_Changed(const QString)), GraphWindow, SLOT(getS2T1(QString)));
    connect(this, SIGNAL(S2T2_Changed(const QString)), GraphWindow, SLOT(getS2T2(QString)));
    connect(this, SIGNAL(S2T3_Changed(const QString)), GraphWindow, SLOT(getS2T3(QString)));

    connect(this, SIGNAL(S3T1_Changed(const QString)), GraphWindow, SLOT(getS3T1(QString)));
    connect(this, SIGNAL(S3T2_Changed(const QString)), GraphWindow, SLOT(getS3T2(QString)));
    connect(this, SIGNAL(S3T3_Changed(const QString)), GraphWindow, SLOT(getS3T3(QString)));

    connect(this, SIGNAL(L1_Changed(const QString)), GraphWindow, SLOT(getL1(QString)));
    connect(this, SIGNAL(L2_Changed(const QString)), GraphWindow, SLOT(getL2(QString)));
    connect(this, SIGNAL(L3_Changed(const QString)), GraphWindow, SLOT(getL3(QString)));


     //ui->textEdit->append(QString::number(ui->listWidget->currentRow()));
    ui->label_2->size();
    ui->label_5->setText(QTime::currentTime().toString("hh:mm:ss"));


    timer = new QTimer();
    singleRead = new QTimer();
    singleTrans = new QTimer();

    singleTrans->setInterval(100);
    singleRead->setInterval(100);
    timer->setInterval(1000);

    singleTrans->setSingleShot(true);
    singleRead->setSingleShot(true);

    connect(singleRead, SIGNAL(timeout()), this, SLOT(slotSingleRead()));
    connect(singleTrans, SIGNAL(timeout()), this, SLOT(slotSingleTrans()));
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));

    timer->start(1000);

    ///////////////////

    unsigned long chver;

    ui->textEdit->append(cm_version);

    if (CiInit() < 0) {
        //printf("CHAI library initialization failed\n");
        exit(1);
    }

    chver = CiGetLibVer();

    ui->textEdit->append("using CHAI " + QString::number(VERMAJ(chver))+"." + QString::number(VERMIN(chver))+"." + QString::number(VERSUB(chver)));
    if(isConnected){
        ui->label_5->setText("connected");
    }
    else{
        ui->label_5->setText("not connected");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::slotTimerAlarm()
{
    if(isConnected){
        ui->label_5->setText("connected");
        //Read();
    }
    else{
        ui->label_5->setText("not connected");
    }
    //ui->label_5->setText(QTime::currentTime().toString("hh:mm:ss"));
}

void MainWindow::on_actionExit_triggered()  //верхняя менюшка
{
    QApplication::quit();
}

void MainWindow::on_StartButton_clicked()
{
    GraphWindow->show();

}

void MainWindow::on_StopButton_clicked()
{
    CiStop(chan);
    CiClose(chan);
    isConnected = false;
}


void MainWindow::on_Connect_clicked()
{

    //ui->textEdit->append(QString::number(ui->listWidget->currentRow()));


    channelForm = ui->listWidget->currentRow();
    baudrateForm = ui->listWidget_2->currentRow();

    if(ui->ListenModBox->isChecked()){
        ui->textEdit->append("checked");
        //listenmodeForm = true;
    }

    if(ui->radioButton->isChecked()) maskForm = 0;
    else if(ui->radioButton_2->isChecked()) maskForm = 1;
    else if(ui->radioButton_3->isChecked()) maskForm = 2;
    else QMessageBox::critical(this, "Warning", "Choose mask");

    if(baudrateForm == -1){
        QMessageBox::critical(this, "Warni"
                                    "ng", "Choose boudrate");
    }
    else if(channelForm == -1){
        QMessageBox::critical(this, "Warning", "Choose channel");
    }
    else{

        switch (ui->listWidget_2->currentRow()) {
        case 0:
            baudrateForm = 125;
            break;
        case 1:
            baudrateForm = 500;
            break;
        case 2:
            baudrateForm = 1000;
            break;
        default:
            break;
        }
        ui->textEdit->append("chan: "+QString::number(ui->listWidget->currentRow()));
        ui->textEdit->append("boud: "+QString::number(ui->listWidget_2->currentRow()));
        ui->textEdit->append("baudrateForm = "+QString::number(baudrateForm));

        ui->listWidget->currentItem()->setText(ui->listWidget->currentItem()->text()+" free");


    }

    ////////Start CAN monitor//////////////

        get_chan();

        get_bitrate();

        ui->textEdit->append("using CAN channel "+QString::number(ui->listWidget->currentRow())+" at " +QString::number(baudrateForm)+ "Kbit/s");

        init_can_channel();
        CiStart(chan);

        isConnected = true;

        canmsg_t tx;
        int ret = 0;
        tx.id = 0x500;
        tx.len = 8;
        for(int j = 0; j < 8; j++){
            tx.data[j] = 0;
        }
        tx.data[0] = 0xff;
        tx.data[6] = 0x41;
        tx.data[5] = 0x37;
        tx.data[4] = 0x75;
        //tx.flags = 0x1;
        ret = CiTransmit(chan, &tx);
        if (ret == 0) {
            //ui->textEdit->append("Succes transmition");
        }
        else {
            ui->textEdit->append("Failed transmition");
        }

        ui->textEdit->insertPlainText("\nTX ID: 0x" + QString::number(tx.id, 16) + "    Length: " + QString::number(tx.len));
        for(int j = 0; j < tx.len; j++){
            ui->textEdit->insertPlainText("    # 0x" + QString::number(tx.data[j], 16));
        }



        tx.id = 0x602;
        for(int j = 0; j < 8; j++){
            tx.data[j] = 0;
        }
        tx.data[0] = 0xa3;
        tx.data[4] = 0x26;
        tx.data[5] = 0xf9;
        tx.data[6] = 0x41;
        ret = CiTransmit(chan, &tx);
        if (ret == 0) {
            //ui->textEdit->append("Succes transmition");
        }
        else {
            ui->textEdit->append("Failed transmition");
        }
        ui->textEdit->insertPlainText("\nTX ID: 0x" + QString::number(tx.id, 16) + "    Length: " + QString::number(tx.len));
        for(int j = 0; j < tx.len; j++){
            ui->textEdit->insertPlainText("    # 0x" + QString::number(tx.data[j], 16));
        }

}


void MainWindow::GetTime(){
    canmsg_t tx;
    int ret = 0;
    tx.id = 0x602;
    tx.len = 8;
    for(int j = 0; j < 8; j++){
        tx.data[j] = 0;
    }
    tx.data[0] = 0x10;
    tx.data[1] = 0xd9;
    tx.data[2] = 0x41;
    tx.data[7] = 0x01;
    tx.data[6] = 0xb2;
    tx.data[5] = 0xdf;
    tx.data[4] = 0xb8;
    //tx.flags = 0x1;
    ret = CiTransmit(chan, &tx);
    if (ret == 0) {
        //ui->textEdit->append("Succes transmition");
    }
    else {
        ui->textEdit->append("Failed transmition");
    }

    printMassege(&tx);
}


void MainWindow::on_GetTimeAverageButton_clicked()
{
    GetTime();
}

void MainWindow::on_TestModOffButton_clicked()
{
    canmsg_t tx;
    int ret = 0;
    tx.id = 0x602;
    tx.len = 8;
    for(int j = 0; j < 8; j++){
        tx.data[j] = 0;
    }
    tx.data[0] = 0xA0;
    tx.data[1] = 0xbe;
    tx.data[2] = 0x42;
    tx.data[7] = 0x01;
    tx.data[6] = 0x8b;
    tx.data[5] = 0xdf;
    tx.data[4] = 0x04;
    //tx.flags = 0x1;
    ret = CiTransmit(chan, &tx);
    if (ret == 0) {
        //ui->textEdit->append("Succes transmition");
    }
    else {
        ui->textEdit->append("Failed transmition");
    }

    printMassege(&tx);
}
void MainWindow::on_TestModOnButton_clicked()
{
    canmsg_t tx;
    int ret = 0;
    tx.id = 0x602;
    tx.len = 8;
    for(int j = 0; j < 8; j++){
        tx.data[j] = 0;
    }
    tx.data[0] = 0xA1;
    tx.data[2] = 0x42;
    tx.data[7] = 0x01;
    tx.data[6] = 0x8b;
    tx.data[5] = 0xdf;
    tx.data[4] = 0x04;
    //tx.flags = 0x1;
    ret = CiTransmit(chan, &tx);
    if (ret == 0) {
        //ui->textEdit->append("Succes transmition");
    }
    else {
        ui->textEdit->append("Failed transmition");
    }

    printMassege(&tx);
}
void MainWindow::on_TransmitButton_clicked()
{

}
void MainWindow::on_ReadButton_clicked()
{
    Read();
}
void MainWindow::on_SettingsButton_clicked()
{
    SettingsWindow Settings;
    Settings.setModal(true);
    Settings.exec();
}




void MainWindow::on_ListenModBox_stateChanged(int arg1)
{
    if(ui->ListenModBox->isChecked()){
        singleTrans->start();
    }
    else if(!(ui->ListenModBox->isChecked())){
        ui->label_5->setText("stopped");
    }
}

void MainWindow::on_lineEdit11_textChanged(const QString &arg1)
{
    emit S1T1_Changed(ui->lineEdit11->text()); // вызываем сигнал, в котором передаём введённые данные
}
void MainWindow::on_lineEdit12_textChanged(const QString &arg1)
{
    emit S1T2_Changed(ui->lineEdit12->text()); // вызываем сигнал, в котором передаём введённые данные
}
void MainWindow::on_lineEdit13_textChanged(const QString &arg1)
{
    emit S1T3_Changed(ui->lineEdit13->text()); // вызываем сигнал, в котором передаём введённые данные
}
void MainWindow::on_lineEdit21_textChanged(const QString &arg1)
{
    emit S2T1_Changed(ui->lineEdit21->text()); // вызываем сигнал, в котором передаём введённые данные
}
void MainWindow::on_lineEdit22_textChanged(const QString &arg1)
{
    emit S2T2_Changed(ui->lineEdit22->text()); // вызываем сигнал, в котором передаём введённые данные
}
void MainWindow::on_lineEdit23_textChanged(const QString &arg1)
{
    emit S2T3_Changed(ui->lineEdit23->text());

}
void MainWindow::on_lineEdit31_textChanged(const QString &arg1)
{
    emit S3T1_Changed(ui->lineEdit31->text());
}
void MainWindow::on_lineEdit32_textChanged(const QString &arg1)
{
    emit S3T2_Changed(ui->lineEdit32->text());
}
void MainWindow::on_lineEdit33_textChanged(const QString &arg1)
{
    emit S3T3_Changed(ui->lineEdit33->text());
}

void MainWindow::on_lineEdit_L1_textChanged(const QString &arg1)
{
    emit L1_Changed(ui->lineEdit_L1->text());
}
void MainWindow::on_lineEdit_L2_textChanged(const QString &arg1)
{
    emit L2_Changed(ui->lineEdit_L2->text());

}
void MainWindow::on_lineEdit_L3_textChanged(const QString &arg1)
{
    emit L3_Changed(ui->lineEdit_L3->text());
}

void MainWindow::on_ExitButton_clicked()
{
    QApplication::quit();
}

void MainWindow::on_Set_L_Button_clicked()
{
    l0[0] = ui->lineEdit_L11->text().toDouble();
    l0[1] = ui->lineEdit_L12->text().toDouble();
    l0[2] = ui->lineEdit_L13->text().toDouble();

    l1[0] = ui->lineEdit_L21->text().toDouble();
    l1[1] = ui->lineEdit_L22->text().toDouble();
    l1[2] = ui->lineEdit_L23->text().toDouble();

    l2[0] = ui->lineEdit_L31->text().toDouble();
    l2[1] = ui->lineEdit_L32->text().toDouble();
    l2[2] = ui->lineEdit_L33->text().toDouble();
}

void MainWindow::on_Get_L_Button_clicked()
{
    ui->lineEdit_L11->setText(QString::number(l0[0]));
    ui->lineEdit_L12->setText(QString::number(l0[1]));
    ui->lineEdit_L13->setText(QString::number(l0[2]));

    ui->lineEdit_L21->setText(QString::number(l1[0]));
    ui->lineEdit_L22->setText(QString::number(l1[1]));
    ui->lineEdit_L23->setText(QString::number(l1[2]));

    ui->lineEdit_L31->setText(QString::number(l2[0]));
    ui->lineEdit_L32->setText(QString::number(l2[1]));
    ui->lineEdit_L33->setText(QString::number(l2[2]));
}
