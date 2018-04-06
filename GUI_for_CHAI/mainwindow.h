#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qtimer>
#include <QTime>
#include "graphplotwindow.h"
#include "settingswindow.h"

#include <chai.h>
#define CMTHR_RET_T unsigned
#define CMTHR_FUNC_DECL __stdcall

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void S1T1_Changed(const QString &text);
    void S1T2_Changed(const QString &text);
    void S1T3_Changed(const QString &text);

    void S2T1_Changed(const QString &text);
    void S2T2_Changed(const QString &text);
    void S2T3_Changed(const QString &text);

    void S3T1_Changed(const QString &text);
    void S3T2_Changed(const QString &text);
    void S3T3_Changed(const QString &text);

    void L1_Changed(const QString &text);
    void L2_Changed(const QString &text);
    void L3_Changed(const QString &text);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //CAN monitor
    void get_chan(void);
    int binfo(void);
    void get_bitrate(void);
    void init_can_channel(void);
    void printMassege(canmsg_t *msg);
    float Fira(unsigned char *xx);
    void Read();
    void GetTime();

private slots:
    void slotTimerAlarm();
    void slotSingleRead();
    void slotSingleTrans();

            //Buttons
    void on_actionExit_triggered();

    void on_StartButton_clicked();

    void on_TransmitButton_clicked();

    void on_SettingsButton_clicked();

    void on_Connect_clicked();


    void on_StopButton_clicked();

    void on_ReadButton_clicked();

    void on_TestModOnButton_clicked();

    void on_TestModOffButton_clicked();

    void on_GetTimeAverageButton_clicked();

    void on_ListenModBox_stateChanged(int arg1);

    void on_lineEdit11_textChanged(const QString &arg1);

    void on_lineEdit31_textChanged(const QString &arg1);

    void on_lineEdit_L1_textChanged(const QString &arg1);

    void on_ExitButton_clicked();

    void on_lineEdit21_textChanged(const QString &arg1);

    void on_lineEdit12_textChanged(const QString &arg1);

    void on_lineEdit13_textChanged(const QString &arg1);

    void on_lineEdit22_textChanged(const QString &arg1);

    void on_lineEdit23_textChanged(const QString &arg1);

    void on_lineEdit32_textChanged(const QString &arg1);

    void on_lineEdit33_textChanged(const QString &arg1);

    void on_lineEdit_L2_textChanged(const QString &arg1);

    void on_lineEdit_L3_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QTimer *timer, *singleRead, *singleTrans;
    GraphPlotWindow *GraphWindow;
};

#endif // MAINWINDOW_H
