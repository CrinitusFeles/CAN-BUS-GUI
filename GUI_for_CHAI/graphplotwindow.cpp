
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
QTime realtime(QTime(0,0,0,0));


GraphPlotWindow::GraphPlotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphPlotWindow)
{
    ui->setupUi(this);

    ui->lineEditInvisible->setVisible(false);
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
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
void GraphPlotWindow::realtimeDataSlot()
{
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

    static QTime time(QTime(0,0,0,0));
    double key = time.elapsed()/1000.0;

    countGraphs = ui->customPlot->graphCount();

    if(countGraphs > 0){
        if(ui->PauseButton->text()=="Resume"){
            //time.setHMS(0,0,0,0);

            //ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectLegend);

            double point = ui->lineEditInvisible->text().toDouble();
            ui->customPlot->xAxis->setRange(point, timeRange, Qt::AlignCenter);
            //ui->lineEdit22->setText(QString::number());
            //ui->lineEdit31->setText("pause " + QString::number(key));
            //ui->lineEdit32->setText(QString::number(ui->customPlot->graph()->dataCount()));



        }
        else{
            static double lastPointKey = 0;
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

                }

                // rescale value (vertical) axis to fit the current data:


                //ui->customPlot->graph(0)->rescaleValueAxis(true, true); //не дает приближать отдельный график
                //ui->customPlot->graph(1)->rescaleValueAxis(true, true);

                lastPointKey = key;
                // make key axis range scroll with the data (at a constant range size of 8):
                ui->customPlot->xAxis->setRange(key, timeRange, Qt::AlignCenter);
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
        time.setHMS(0,0,0,0);
        sum = 0;
        for(int i = 0; i < countGraphs; i++){
            ui->customPlot->graph(i)->data()->clear();
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
        dataTimer.start(50);
        ui->customPlot->replot();

        //ui->statusBar->showMessage("Paused");
    }
    else{
        //pauseTimer.start(50);
        ui->PauseButton->setText("Pause");

        //ui->lineEdit31->setText(QString::number(currenttime));
        ui->customPlot->replot();
    }
}

int count = 0;
void GraphPlotWindow::on_SaveButton_clicked()
{
    count++;
    if (ui->comboBox->currentText() == "PNG") {
        QString fileName("D:/Qt/Projects/ReleaseProject/GUIwithTimeGraph/Graphics/customPlot"+QString::number(count)+".png");
        QFile file(fileName);

        if (!file.open(QIODevice::WriteOnly))
        {
            qDebug() << file.errorString();
        } else {
            ui->customPlot->savePng(fileName);
        }
    }
    if(ui->comboBox->currentText() == "JPG"){
        QString fileName("D:/Qt/Projects/ReleaseProject/GUIwithTimeGraph/Graphics/customPlot"+QString::number(count)+".jpg");
        QFile file(fileName);

        if (!file.open(QIODevice::WriteOnly))
        {
            qDebug() << file.errorString();
        } else {
            ui->customPlot->saveJpg(fileName);
        }
    }
    if(ui->comboBox->currentText() == "BMP"){
        QString fileName("D:/Qt/Projects/ReleaseProject/GUIwithTimeGraph/Graphics/customPlot"+QString::number(count)+".bmp");
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
    ui->addButton_11->setEnabled(false);
    CreateNewGraph("S1T1", "red");
}
void GraphPlotWindow::on_addButton_12_clicked()
{
    ui->addButton_12->setEnabled(false);
    CreateNewGraph("S1T2", "green");
}
void GraphPlotWindow::on_addButton_13_clicked()
{
    ui->addButton_13->setEnabled(false);
    CreateNewGraph("S1T3", "blue");
}


void GraphPlotWindow::on_addButton_21_clicked()
{
    ui->addButton_21->setEnabled(false);
    CreateNewGraph("S2T1", "yellow");
}
void GraphPlotWindow::on_addButton_22_clicked()
{
    ui->addButton_22->setEnabled(false);
    CreateNewGraph("S2T2", "black");
}
void GraphPlotWindow::on_addButton_23_clicked()
{
    ui->addButton_23->setEnabled(false);
    CreateNewGraph("S2T3", 25, 100, 200);
}


void GraphPlotWindow::on_addButton_31_clicked()
{
    ui->addButton_31->setEnabled(false);
    CreateNewGraph("S3T1", 125, 150, 200);
}
void GraphPlotWindow::on_addButton_32_clicked()
{
    ui->addButton_32->setEnabled(false);
    CreateNewGraph("S3T2", 255, 10, 200);
}
void GraphPlotWindow::on_addButton_33_clicked()
{
    ui->addButton_33->setEnabled(false);
    CreateNewGraph("S3T3", 25, 200, 200);
}

void GraphPlotWindow::on_addButton_L1_clicked()
{
    ui->addButton_L1->setEnabled(false);
    CreateNewGraph("L1", 255, 200, 20);
}
void GraphPlotWindow::on_addButton_L2_clicked()
{
    ui->addButton_L2->setEnabled(false);
    CreateNewGraph("L2", 55, 66, 180);
}
void GraphPlotWindow::on_addButton_L3_clicked()
{
    ui->addButton_L3->setEnabled(false);
    CreateNewGraph("L3", 5, 156, 180);
}

void GraphPlotWindow::on_pushButton_clicked()
{
    ui->addButton_11->setEnabled(false);
    CreateNewGraph("S1T1", "red");
    ui->addButton_12->setEnabled(false);
    CreateNewGraph("S1T2", "green");
    ui->addButton_13->setEnabled(false);
    CreateNewGraph("S1T3", "blue");
    ui->addButton_21->setEnabled(false);
    CreateNewGraph("S2T1", "yellow");
    ui->addButton_22->setEnabled(false);
    CreateNewGraph("S2T2", "black");
    ui->addButton_23->setEnabled(false);
    CreateNewGraph("S2T3", 25, 100, 200);
    ui->addButton_31->setEnabled(false);
    CreateNewGraph("S3T1", 125, 150, 200);
    ui->addButton_32->setEnabled(false);
    CreateNewGraph("S3T2", 255, 10, 200);
    ui->addButton_33->setEnabled(false);
    CreateNewGraph("S3T3", 25, 200, 200);
    ui->addButton_L1->setEnabled(false);
    CreateNewGraph("L1", 255, 200, 20);
    ui->addButton_L2->setEnabled(false);
    CreateNewGraph("L2", 55, 66, 180);
    ui->addButton_L3->setEnabled(false);
    CreateNewGraph("L3", 5, 156, 180);
}

void GraphPlotWindow::on_horizontalSlider_sliderMoved(int position)
{
    timeRange = position;
}
