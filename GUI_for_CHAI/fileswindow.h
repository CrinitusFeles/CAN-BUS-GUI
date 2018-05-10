#ifndef FILESWINDOW_H
#define FILESWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QDir>
namespace Ui {
class FilesWindow;
}

class FilesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FilesWindow(QWidget *parent = 0);
    ~FilesWindow();

private slots:


    void on_listView_doubleClicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

signals:
    openWindow();
    sendPlotFile(const QString &fileName);

private:
    Ui::FilesWindow *ui;
    QFileSystemModel *model;
};

#endif // FILESWINDOW_H
