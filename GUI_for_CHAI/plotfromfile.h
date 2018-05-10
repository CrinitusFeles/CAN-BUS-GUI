#ifndef PLOTFROMFILE_H
#define PLOTFROMFILE_H

#include <QMainWindow>
#include "qcustomplot.h"
namespace Ui {
class PlotFromFile;
}

class PlotFromFile : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlotFromFile(QWidget *parent = 0);
    ~PlotFromFile();
private slots:
    void CreateNewGraph(QString graphName, QString color);

    void on_Scale_sliderMoved(int position);

    void on_xAxisReplace_sliderMoved(int position);

    void on_spinBox_valueChanged(int arg1);

    void on_SaveButton_clicked();

    void getPlotFile(QString fileName);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_OpenButton_clicked();

signals:
    openWindow();
    OpenFileSystem();

private:
    Ui::PlotFromFile *ui;

};

#endif // PLOTFROMFILE_H
