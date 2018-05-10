#include "fileswindow.h"
#include "ui_fileswindow.h"

FilesWindow::FilesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FilesWindow)
{
    ui->setupUi(this);

    model = new QFileSystemModel(this);
    model->setFilter(QDir::QDir::AllEntries);
    //auto index = model->index(QDir::currentPath());
    //ui->listView->setRootIndex(index);
    model->setRootPath(QApplication::applicationDirPath());
    ui->listView->setModel(model);
    ui->listView->setRootIndex(model->index(QApplication::applicationDirPath()));
    //ui->listView->setRootIndex(model->index(QApplication::applicationDirPath()));

    //connect(ui->listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_listWidget_doubleClicked(QModelIndex)));
}

FilesWindow::~FilesWindow()
{
    delete ui;
}



void FilesWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    QFileInfo fileInfo = model->fileInfo(index);


    if(fileInfo.fileName() == ".."){
        QDir dir = fileInfo.dir();
        dir.cdUp();
        ui->listView->setRootIndex(model->index(dir.absolutePath()));
    }
    else if(fileInfo.fileName() == "."){
        ui->listView->setRootIndex(model->index(""));
    }
    else if(fileInfo.isDir()){
        ui->listView->setRootIndex(index);
    }
    else if(fileInfo.isFile()){
        emit sendPlotFile(QString(fileInfo.fileName()));
        //ui->lineEdit->setText(fileInfo.fileName()+" "+fileInfo.filePath());
        this->close();
    }
}

void FilesWindow::on_pushButton_2_clicked()
{
    this->close();
    delete ui;
}

void FilesWindow::on_pushButton_clicked()
{
    emit sendPlotFile(model->fileInfo(ui->listView->currentIndex()).fileName());
    //ui->lineEdit->setText(fileInfo.fileName());
    this->close();
}
