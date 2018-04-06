#include "graphplotwindow.h"
#include "settingswindow.h"
#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //GraphPlotWindow w;
    MainWindow d;
    d.show();

    //w.show();
    return a.exec();
}
