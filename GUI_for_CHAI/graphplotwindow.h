#ifndef GRAPHPLOTWINDOW_H
#define GRAPHPLOTWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

#include <QTimer>

namespace Ui {
class GraphPlotWindow;
}

class GraphPlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphPlotWindow(QWidget *parent = 0);
    ~GraphPlotWindow();

    void CreateNewGraph(QString graphName, QString color);
    void CreateNewGraph(QString graphName, int r, int g, int b);

signals:
    void openWindow();

public slots:
    void getS1T1(QString str);
    void getS1T2(QString str);
    void getS1T3(QString str);

    void getS2T1(QString str);
    void getS2T2(QString str);
    void getS2T3(QString str);

    void getS3T1(QString str);
    void getS3T2(QString str);
    void getS3T3(QString str);

    void getL1(QString str);
    void getL2(QString str);
    void getL3(QString str);

private slots:
  void realtimeDataSlot();

            //Buttons:
  void on_CloseButton_clicked();

  void on_PauseButton_toggled(bool checked);

  void on_SaveButton_clicked();



  void on_addButton_11_clicked();

  void on_addButton_21_clicked();

  void on_addButton_31_clicked();

  void on_addButton_12_clicked();

  void on_addButton_13_clicked();

  void on_addButton_22_clicked();

  void on_addButton_23_clicked();

  void on_addButton_32_clicked();

  void on_addButton_33_clicked();

  void on_addButton_L1_clicked();

  void on_addButton_L2_clicked();

  void on_addButton_L3_clicked();

  void on_pushButton_clicked();

  void on_horizontalSlider_sliderMoved(int position);

  void on_horizontalSlider_min_sliderMoved(int position);

  void on_spinBox_sec_valueChanged(int arg1);

  void on_spinBox__min_valueChanged(int arg1);

  void on_xAxis_Slider_sliderMoved(int position);

  void on_Days_slider_sliderMoved(int position);

  void on_RestartButton_clicked();

  void on_addButton_D1_clicked();


private:
    Ui::GraphPlotWindow *ui;
    QTimer dataTimer, pauseTimer;

};

#endif // GRAPHPLOTWINDOW_H
