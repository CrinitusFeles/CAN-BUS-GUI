#include "plotfromfile.h"
#include "ui_plotfromfile.h"
#include <QMessageBox>
QFile File;
void PlotFromFile::CreateNewGraph(QString graphName, QString color){
    ui->customPlot->addGraph();
    ui->customPlot->graph()->setPen(QPen(QColor(color)));
    ui->customPlot->graph()->setName(graphName);
    ui->customPlot->graph()->addToLegend();
}
void PlotFromFile::getPlotFile(QString fileName){
    ui->lineEdit->setText(fileName);
    File.setFileName(fileName);
}
PlotFromFile::PlotFromFile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotFromFile)
{
    ui->setupUi(this);

    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->yAxis->setRange(-1.2, 1.2);
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectLegend);
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("day %d\n%h:%m:%s");
    ui->customPlot->xAxis->setTicker(timeTicker);
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));


}

PlotFromFile::~PlotFromFile()
{
    delete ui;
}



void PlotFromFile::on_Scale_sliderMoved(int position)
{
    if(ui->customPlot->graphCount() != 0){
        ui->Scale->setMinimum(1);
        ui->Scale->setMaximum(3600*ui->spinBox->value());
        ui->customPlot->xAxis->setRange(ui->xAxisReplace->value(), ui->Scale->value(), Qt::AlignCenter); //dont work
        ui->customPlot->replot();
    }
}

void PlotFromFile::on_xAxisReplace_sliderMoved(int position)
{
    if(ui->customPlot->graphCount() != 0){
        ui->customPlot->xAxis->setRange(ui->xAxisReplace->value(), ui->Scale->value(), Qt::AlignCenter); //dont work
        ui->customPlot->replot();
    }
}

void PlotFromFile::on_spinBox_valueChanged(int arg1)
{
    if(ui->customPlot->graphCount() != 0){
        ui->Scale->setMinimum(1);
        ui->Scale->setMaximum(3600*ui->spinBox->value());
        ui->customPlot->replot();
    }

}

void PlotFromFile::on_SaveButton_clicked()
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
        QString fileName("GraphsFolder/graph "+QDate::currentDate().toString("dd.MM.yy")+" _ "+QTime::currentTime().toString("hh.mm.ss")+".jpg");
        QFile file(fileName);

        if (!file.open(QIODevice::WriteOnly))
        {
            qDebug() << file.errorString();
        } else {
            ui->customPlot->saveJpg(fileName);
        }
    }
    if(ui->comboBox->currentText() == "BMP"){
        QString fileName("GraphsFolder/graph "+QDate::currentDate().toString("dd.MM.yy")+" _ "+QTime::currentTime().toString("hh.mm.ss")+".bmp");
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            qDebug() << file.errorString();
        } else {
            ui->customPlot->saveJpg(fileName);
        }
    }
    if(ui->comboBox->currentText() == "PDF"){
        QString fileName("GraphsFolder/graph "+QDate::currentDate().toString("dd.MM.yy")+" _ "+QTime::currentTime().toString("hh.mm.ss")+".pdf");
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            qDebug() << file.errorString();
        } else {
            ui->customPlot->saveJpg(fileName);
        }
    }

}

void PlotFromFile::on_pushButton_clicked()
{
    for(int i = 0; i < ui->customPlot->graphCount(); i++){
        ui->customPlot->graph(i)->data()->clear();
    }
    ui->customPlot->legend->clear();
    ui->customPlot->replot();
    CreateNewGraph("1", "blue");

    if(!File.open(QIODevice::ReadOnly | QIODevice::Text)) QMessageBox::critical(this, "Warning", "Error file");
    else{
        QByteArray header = File.read(86);//header +/n
        //ui->textEdit->append(header);

        static double lastPointKey = 0;
        int day = 0;
        QString numberArray = File.readAll();
        QStringList strokes = numberArray.split("\n");
        QStringList numbers;
        double key, data;
        for(int i = 0; i < strokes.size(); i++){
            numbers += strokes.at(i).split("\t");


        }
        QString str;
        for(int i = 0; i < numbers.size(); i++){
            if(i % 14 == 12){
                //ui->textEdit->insertPlainText(numbers.at(i)+"\t");

                data = QString(numbers.at(i)).toDouble();
            }
            if(i % 14 == 13){

                str = numbers.at(i);
                key = day*86400+(QString(str[0]).toInt()*10 + QString(str[1]).toInt())*3600 + (QString(str[3]).toInt()*10 +
                           QString(str[4]).toInt())*60 + QString(str[6]).toInt()*10 + QString(str[7]).toInt();
                //ui->textEdit->insertPlainText(QString::number(time)+"\n");
                if(key < lastPointKey || key == 86400) {
                    day++;
                    key = day*86400+(QString(str[0]).toInt()*10 + QString(str[1]).toInt())*3600 + (QString(str[3]).toInt()*10 +
                               QString(str[4]).toInt())*60 + QString(str[6]).toInt()*10 + QString(str[7]).toInt();
                }
                ui->customPlot->graph()->addData(key, data);

                lastPointKey = key;
            }


        }
        str = numbers.at(13);
        ui->spinBox->setMinimum(1);
        ui->xAxisReplace->setMinimum((QString(str[0]).toInt()*10 + QString(str[1]).toInt())*3600 + (QString(str[3]).toInt()*10 +
                QString(str[4]).toInt())*60 + QString(str[6]).toInt()*10 + QString(str[7]).toInt());
        ui->xAxisReplace->setMaximum((int)key);
        ui->xAxisReplace->setValue((int)key);
        ui->Scale->setMinimum(1);
        ui->Scale->setValue(5);
        ui->Scale->setMaximum(3600*ui->spinBox->value());
        ui->customPlot->xAxis->setRange(key, 12, Qt::AlignCenter);
        ui->customPlot->yAxis->setRange(data, 12, Qt::AlignCenter);
        File.close();
        ui->customPlot->replot();
    }
}

void PlotFromFile::on_pushButton_2_clicked()
{
    for(int i = 0; i < ui->customPlot->graphCount(); i++){
        ui->customPlot->graph(i)->data()->clear();

    }
    ui->customPlot->legend->clear();
    ui->customPlot->replot();
}

void PlotFromFile::on_pushButton_3_clicked()
{
    this->close();
}

void PlotFromFile::on_OpenButton_clicked()
{
    emit OpenFileSystem();
}
