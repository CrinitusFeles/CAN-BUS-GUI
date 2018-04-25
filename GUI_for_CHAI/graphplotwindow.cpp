
#include "ui_graphplotwindow.h"
#include "graphplotwindow.h"

void GraphPlotWindow::CreateNewGraph(QString graphName, QString color){
    ui->customPlot->addGraph();
    ui->customPlot->graph()->setPen(QPen(QColor(color)));
    ui->customPlot->graph()->setName(graphName);
    ui->customPlot->graph()->addToLegend();
}
void GraphPlotWindow::CreateNewGraph(QString graphName, int r, int g, int b){
    ui->customPlot->addGraph();
    ui->customPlot->graph()->setPen(QPen(QColor(r, g, b)));
    ui->customPlot->graph()->setName(graphName);
    ui->customPlot->graph()->addToLegend();
}


GraphPlotWindow::GraphPlotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphPlotWindow)
{
    ui->setupUi(this);

    ui->lineEditInvisible->setVisible(false);
    ui->lineEdit_Invisible2->setVisible(false);
    ui->lineStartProgramTime->setVisible(false);
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("day %d\n%h:%m:%s");
    ui->customPlot->xAxis->setTicker(timeTicker);
    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->yAxis->setRange(-1.2, 1.2);
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectLegend);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    }

GraphPlotWindow::~GraphPlotWindow()
{
    delete ui;
}
void GraphPlotWindow::getS1T1(QString str){
    ui->lineEdit11->setText(str);
}
void GraphPlotWindow::getS1T2(QString str){
    ui->lineEdit12->setText(str);
}
void GraphPlotWindow::getS1T3(QString str){
    ui->lineEdit13->setText(str);
}

void GraphPlotWindow::getS2T1(QString str){
    ui->lineEdit21->setText(str);
}
void GraphPlotWindow::getS2T2(QString str){
    ui->lineEdit22->setText(str);
}
void GraphPlotWindow::getS2T3(QString str){
    ui->lineEdit23->setText(str);
}

void GraphPlotWindow::getS3T1(QString str){
    ui->lineEdit31->setText(str);
}
void GraphPlotWindow::getS3T2(QString str){
    ui->lineEdit32->setText(str);
}
void GraphPlotWindow::getS3T3(QString str){
    ui->lineEdit33->setText(str);
}


void GraphPlotWindow::getL1(QString str){
    ui->lineEdit_L1->setText(str);
}
void GraphPlotWindow::getL2(QString str){
    ui->lineEdit_L2->setText(str);
}
void GraphPlotWindow::getL3(QString str){
    ui->lineEdit_L3->setText(str);
}

double s1t1, s1t2, s1t3, s2t1, s2t2, s2t3, s3t1, s3t2,  s3t3, L1, L2, L3;
int countGraphs;
unsigned int sum;
int timeRange = 12;
double stopPosition;
int xAxis_position;
//double lastPointKey = 0;
int days = 0;
bool isStarted = false;
double deltaLevel;
static double lastPointKey = 0;
void GraphPlotWindow::realtimeDataSlot()
{
    timeRange = ui->Days_slider->value()*ui->spinBox_day->value()+ui->horizontalSlider->value()*ui->spinBox_sec->value() + ui->horizontalSlider_min->value()*ui->spinBox__min->value();
    int day, hour, min, sec;
    day = timeRange / 86400;
    hour = timeRange %86400 / 3600;
    min = timeRange %86400 % 3600 / 60;
    sec = timeRange %86400 % 3600 % 60;
    ui->label_timeScale->setText(QString::number(day) + " d :" +QString::number(hour) + " h :" + QString::number(min) + " min :" + QString::number(sec) + " sec");


    dataTimer.setSingleShot(false);
    s1t1 = (double) ui->lineEdit11->text().toDouble();
    s1t2 = (double) ui->lineEdit12->text().toDouble();
    s1t3 = (double) ui->lineEdit13->text().toDouble();
    s2t1 = (double) ui->lineEdit21->text().toDouble();
    s2t2 = (double) ui->lineEdit22->text().toDouble();
    s2t3 = (double) ui->lineEdit23->text().toDouble();
    s3t1 = (double) ui->lineEdit31->text().toDouble();
    s3t2 = (double) ui->lineEdit32->text().toDouble();
    s3t3 = (double) ui->lineEdit33->text().toDouble();

    L1 = (double) ui->lineEdit_L1->text().toDouble();
    L2 = (double) ui->lineEdit_L2->text().toDouble();
    L3 = (double) ui->lineEdit_L3->text().toDouble();

    deltaLevel = L2 - L1;
    ui->lineEditDelta_1->setText(QString::number(deltaLevel));

    static QTime time(QTime(0,0,0,0));
    double key = time.elapsed()/1000.0;

    //ui->lineEdit_L3->setText(QString::number(key));
    //ui->lineEdit_L1->setText(QString::number(lastPointKey));
    key = key + 86400*days;
    ui->lineEdit_Invisible2->setText(QString::number(int(key)%86400/3600)+"."+QString::number(int(key)%3600/60)+"."+QString::number(int(key)%3600%60));
    if(lastPointKey > key) days++;
    countGraphs = ui->customPlot->graphCount();
    //ui->lineEdit_L2->setText(QString::number(countGraphs));
    //ui->lineEdit11->setText(QString::number(days));

    if(countGraphs > 0){
        if(ui->PauseButton->text()=="Resume"){
            //time.setHMS(0,0,0,0);

            //ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectLegend);

            int stopTime = ui->lineEditInvisible->text().toInt();
            ui->xAxis_Slider->setMaximum(stopTime);
            ui->customPlot->xAxis->setRange(ui->xAxis_Slider->value(), timeRange, Qt::AlignCenter); //dont work
            //ui->lineEdit22->setText(QString::number());
            //ui->lineEdit31->setText("pause ");
            //ui->lineEdit32->setText(QString::number(ui->customPlot->graph()->dataCount()));
            ui->customPlot->replot();


        }
        else{
            lastPointKey = 0;

            if ((key)-lastPointKey > 0.002) // at most add point every 2 ms
            {
                ui->lineEditInvisible->setText(QString::number(key));
                // add  data to lines:
                //добавить установку кол-ва графиков из меню

                //ui->customPlot->graph(0)->addData(key, qSin(key)+param+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
                //ui->customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));

                for(int i = 0; i < countGraphs; i++){

                    if(ui->customPlot->graph(i)->name() == "S1T1") ui->customPlot->graph(i)->addData(key, s1t1);
                    if(ui->customPlot->graph(i)->name() == "S1T2") ui->customPlot->graph(i)->addData(key, s1t2);
                    if(ui->customPlot->graph(i)->name() == "S1T3") ui->customPlot->graph(i)->addData(key, s1t3);

                    if(ui->customPlot->graph(i)->name() == "S2T1") ui->customPlot->graph(i)->addData(key, s2t1);
                    if(ui->customPlot->graph(i)->name() == "S2T2") ui->customPlot->graph(i)->addData(key, s2t2);
                    if(ui->customPlot->graph(i)->name() == "S2T3") ui->customPlot->graph(i)->addData(key, s2t3);

                    if(ui->customPlot->graph(i)->name() == "S3T1") ui->customPlot->graph(i)->addData(key, s3t1);
                    if(ui->customPlot->graph(i)->name() == "S3T2") ui->customPlot->graph(i)->addData(key, s3t2);
                    if(ui->customPlot->graph(i)->name() == "S3T3") ui->customPlot->graph(i)->addData(key, s3t3);

                    if(ui->customPlot->graph(i)->name() == "L1") ui->customPlot->graph(i)->addData(key, L1);
                    if(ui->customPlot->graph(i)->name() == "L2") ui->customPlot->graph(i)->addData(key, L2);
                    if(ui->customPlot->graph(i)->name() == "L3") ui->customPlot->graph(i)->addData(key, L3);

                    if(ui->customPlot->graph(i)->name() == "D1") ui->customPlot->graph(i)->addData(key, deltaLevel);

                }

                // rescale value (vertical) axis to fit the current data:


                //ui->customPlot->graph(0)->rescaleValueAxis(true, true); //не дает приближать отдельный график
                //ui->customPlot->graph(1)->rescaleValueAxis(true, true);

                lastPointKey = key;
                // make key axis range scroll with the data (at a constant range size of 8):
                if(ui->RTmode->isChecked()){
                    ui->customPlot->xAxis->setRange(key, timeRange, Qt::AlignCenter);
                }
                else{
                    ui->xAxis_Slider->setMaximum(key);
                    ui->customPlot->xAxis->setRange(ui->xAxis_Slider->value(), timeRange, Qt::AlignCenter);
                }
                ui->customPlot->replot();

                //ui->customPlot->graph(0)->set

            }
        }

        // calculate frames per second:
        static double lastFpsKey;
        static int frameCount;

        ++frameCount;
        if (key-lastFpsKey > 2) // average fps over 2 seconds
        {
            for(int i = 0; i < countGraphs; i++){
                sum+=ui->customPlot->graph(i)->data()->size();
            }
            ui->statusBar->showMessage(QString("%1 FPS, Total Data points: %2").arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
            .arg(sum), 0);
            lastFpsKey = key;
            frameCount = 0;
        }
    }
    //if(ui->HideButton->isDown()) CreateNewGraph("new graph");

    if(ui->RestartButton->isDown()){
        int ret = QMessageBox::question(this, "Attention!", "Are you sure?");
        if(ret == QMessageBox::Yes){
            time.setHMS(0,0,0,0);
            sum = 0;
            for(int i = 0; i < countGraphs; i++){
                ui->customPlot->graph(i)->data()->clear();
            }
        }

        ui->customPlot->replot();
    }




}

void GraphPlotWindow::on_CloseButton_clicked()
{
    this->close();
}

void GraphPlotWindow::on_PauseButton_toggled(bool checked)
{
    if(!checked){
        ui->PauseButton->setText("Resume");

        dataTimer.stop();


        double stopTime = ui->lineEditInvisible->text().toDouble();
        ui->xAxis_Slider->setMaximum(stopTime+10);
        ui->xAxis_Slider->setMinimum(ui->lineStartProgramTime->text().toDouble());

        //ui->lineEdit31->setText(QString::number(stopTime));
        //ui->lineEdit32->setText(QString::number(ui->customPlot->graph()->dataCount()));
        ui->xAxis_Slider->setValue(stopTime+1);


        ui->customPlot->replot();


        //ui->customPlot->replot();

        //ui->statusBar->showMessage("Paused");
    }
    else{
        QTime startProgram(0,0,0);
        if(!isStarted){

            ui->lineStartProgramTime->setText(QString::number(startProgram.elapsed()/1000));

            isStarted = true;
        }
        ui->PauseButton->setText("Pause");
        dataTimer.start(50);
        ui->customPlot->replot();

        //ui->lineEdit31->setText(QString::number(currenttime));
        //ui->customPlot->replot();
    }
}

void GraphPlotWindow::on_SaveButton_clicked()
{
    QDir().mkdir("GraphsFolder");

    if (ui->comboBox->currentText() == "PNG") {
        QString fileName("GraphsFolder/graph "+QDate::currentDate().toString("dd.MM.yy")+" _ "+QTime::currentTime().toString("hh.mm.ss")+".png");
        QFile file(fileName);

        if (!file.open(QIODevice::WriteOnly))
        {
            qDebug() << file.errorString();
        } else {
            ui->customPlot->savePng(fileName);
        }
    }
    if(ui->comboBox->currentText() == "JPG"){
        QString fileName("GraphsFolder/graph "+ui->lineEdit_Invisible2->text()+".jpg");
        QFile file(fileName);

        if (!file.open(QIODevice::WriteOnly))
        {
            qDebug() << file.errorString();
        } else {
            ui->customPlot->saveJpg(fileName);
        }
    }
    if(ui->comboBox->currentText() == "BMP"){
        QString fileName("GraphsFolder/graph "+ui->lineEdit_Invisible2->text()+".bmp");
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            qDebug() << file.errorString();
        } else {
            ui->customPlot->saveJpg(fileName);
        }
    }
    if(ui->comboBox->currentText() == "PDF"){
        QString fileName("GraphsFolder/graph "+ui->lineEdit_Invisible2->text()+".pdf");
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            qDebug() << file.errorString();
        } else {
            ui->customPlot->saveJpg(fileName);
        }
    }

}


void GraphPlotWindow::on_addButton_11_clicked()
{
    ui->pushButton->setEnabled(false);
    ui->addButton_11->setEnabled(false);
    CreateNewGraph("S1T1", "red");
}
void GraphPlotWindow::on_addButton_12_clicked()
{
    ui->pushButton->setEnabled(false);
    ui->addButton_12->setEnabled(false);
    CreateNewGraph("S1T2", "red");
}
void GraphPlotWindow::on_addButton_13_clicked()
{
    ui->pushButton->setEnabled(false);
    ui->addButton_13->setEnabled(false);
    CreateNewGraph("S1T3", "red");
}


void GraphPlotWindow::on_addButton_21_clicked()
{
    ui->pushButton->setEnabled(false);
    ui->addButton_21->setEnabled(false);
    CreateNewGraph("S2T1", "blue");
}
void GraphPlotWindow::on_addButton_22_clicked()
{
    ui->pushButton->setEnabled(false);
    ui->addButton_22->setEnabled(false);
    CreateNewGraph("S2T2", "blue");
}
void GraphPlotWindow::on_addButton_23_clicked()
{
    ui->pushButton->setEnabled(false);
    ui->addButton_23->setEnabled(false);
    CreateNewGraph("S2T3", "blue");
}


void GraphPlotWindow::on_addButton_31_clicked()
{
    ui->pushButton->setEnabled(false);
    ui->addButton_31->setEnabled(false);
    CreateNewGraph("S3T1", "green");
}
void GraphPlotWindow::on_addButton_32_clicked()
{
    ui->pushButton->setEnabled(false);
    ui->addButton_32->setEnabled(false);
    CreateNewGraph("S3T2", "green");
}
void GraphPlotWindow::on_addButton_33_clicked()
{
    ui->pushButton->setEnabled(false);
    ui->addButton_33->setEnabled(false);
    CreateNewGraph("S3T3", "green");
}

void GraphPlotWindow::on_addButton_L1_clicked()
{
    ui->pushButton->setEnabled(false);
    ui->addButton_L1->setEnabled(false);
    CreateNewGraph("L1", "red");
}
void GraphPlotWindow::on_addButton_L2_clicked()
{
    ui->pushButton->setEnabled(false);
    ui->addButton_L2->setEnabled(false);
    CreateNewGraph("L2", "blue");
}
void GraphPlotWindow::on_addButton_L3_clicked()
{
    ui->pushButton->setEnabled(false);
    ui->addButton_L3->setEnabled(false);
    CreateNewGraph("L3", "green");
}

void GraphPlotWindow::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);
    ui->addButton_11->setEnabled(false);
    CreateNewGraph("S1T1", "red");
    ui->addButton_12->setEnabled(false);
    CreateNewGraph("S1T2", "red");
    ui->addButton_13->setEnabled(false);
    CreateNewGraph("S1T3", "red");
    ui->addButton_21->setEnabled(false);
    CreateNewGraph("S2T1", "blue");
    ui->addButton_22->setEnabled(false);
    CreateNewGraph("S2T2", "blue");
    ui->addButton_23->setEnabled(false);
    CreateNewGraph("S2T3", "blue");
    ui->addButton_31->setEnabled(false);
    CreateNewGraph("S3T1", "green");
    ui->addButton_32->setEnabled(false);
    CreateNewGraph("S3T2", "green");
    ui->addButton_33->setEnabled(false);
    CreateNewGraph("S3T3", "green");
    ui->addButton_L1->setEnabled(false);
    CreateNewGraph("L1", "red");
    ui->addButton_L2->setEnabled(false);
    CreateNewGraph("L2", "blue");
    ui->addButton_L3->setEnabled(false);
    CreateNewGraph("L3", "green");
    ui->addButton_D1->setEnabled(false);
    CreateNewGraph("D1", "black");
}

void GraphPlotWindow::on_horizontalSlider_sliderMoved(int position)
{
    timeRange = position;
    if(ui->PauseButton->text()=="Resume"){
        timeRange = ui->Days_slider->value()*ui->spinBox_day->value()+ui->horizontalSlider->value()*ui->spinBox_sec->value() + ui->horizontalSlider_min->value()*ui->spinBox__min->value();
        int day, hour, min, sec;
        day = timeRange / 86400;
        hour = timeRange %86400 / 3600;
        min = timeRange %86400 % 3600 / 60;
        sec = timeRange %86400 % 3600 % 60;
        ui->label_timeScale->setText(QString::number(day) + " d :" +QString::number(hour) + " h :" + QString::number(min) + " min :" + QString::number(sec) + " sec");
        ui->customPlot->xAxis->setRange(ui->xAxis_Slider->value(), timeRange, Qt::AlignCenter); //dont work
        ui->customPlot->replot();
    }
    ui->customPlot->replot();
}

void GraphPlotWindow::on_horizontalSlider_min_sliderMoved(int position)
{
    timeRange = position;
    if(ui->PauseButton->text()=="Resume"){
        timeRange = ui->Days_slider->value()*ui->spinBox_day->value()+ui->horizontalSlider->value()*ui->spinBox_sec->value() + ui->horizontalSlider_min->value()*ui->spinBox__min->value();
        int day, hour, min, sec;
        day = timeRange / 86400;
        hour = timeRange %86400 / 3600;
        min = timeRange %86400 % 3600 / 60;
        sec = timeRange %86400 % 3600 % 60;
        ui->label_timeScale->setText(QString::number(day) + " d :" +QString::number(hour) + " h :" + QString::number(min) + " min :" + QString::number(sec) + " sec");
        ui->customPlot->xAxis->setRange(ui->xAxis_Slider->value(), timeRange, Qt::AlignCenter); //dont work
        ui->customPlot->replot();
    }
    ui->customPlot->replot();
}

void GraphPlotWindow::on_spinBox_sec_valueChanged(int arg1)
{
    ui->customPlot->replot();
}

void GraphPlotWindow::on_spinBox__min_valueChanged(int arg1)
{
    ui->customPlot->replot();
}

void GraphPlotWindow::on_xAxis_Slider_sliderMoved(int position)
{
    xAxis_position = position;
    ui->RTmode->setChecked(false);
    if(ui->PauseButton->text()=="Resume"){
        timeRange = ui->Days_slider->value()*ui->spinBox_day->value()+ui->horizontalSlider->value()*ui->spinBox_sec->value() + ui->horizontalSlider_min->value()*ui->spinBox__min->value();

        ui->customPlot->xAxis->setRange(ui->xAxis_Slider->value(), timeRange, Qt::AlignCenter); //dont work
        ui->customPlot->replot();
    }
}

void GraphPlotWindow::on_Days_slider_sliderMoved(int position)
{
    if(ui->PauseButton->text()=="Resume"){
        timeRange = ui->Days_slider->value()*ui->spinBox_day->value()+ui->horizontalSlider->value()*ui->spinBox_sec->value() + ui->horizontalSlider_min->value()*ui->spinBox__min->value();
        int day, hour, min, sec;
        day = timeRange / 86400;
        hour = timeRange %86400 / 3600;
        min = timeRange %86400 % 3600 / 60;
        sec = timeRange %86400 % 3600 % 60;
        ui->label_timeScale->setText(QString::number(day) + " d :" +QString::number(hour) + " h :" + QString::number(min) + " min :" + QString::number(sec) + " sec");
        ui->customPlot->xAxis->setRange(ui->xAxis_Slider->value(), timeRange, Qt::AlignCenter); //dont work
        ui->customPlot->replot();
    }
}

void GraphPlotWindow::on_RestartButton_clicked()
{

    int ret = QMessageBox::question(this, "Attention!", "Are you sure?");
    if(ret == QMessageBox::Yes){
        for(int i = 0; i < countGraphs; i++){
            ui->customPlot->graph(i)->data()->clear();
        }
    }
    ui->customPlot->replot();

}
