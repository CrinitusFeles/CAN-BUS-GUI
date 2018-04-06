#include "settingswindow.h"
#include "graphplotwindow.h"
#include "ui_settingswindow.h"
#include <QMessageBox>


SettingsWindow::SettingsWindow(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_Connect_clicked()
{
    if(ui->radioButton->isChecked() || ui->radioButton_2->isChecked() || ui->radioButton_3->isChecked()){
        this->close();
    } else{
        QMessageBox::critical(this, "Warning", "Choose format");
    }
    //if(ui->BoudrateEdit->get)

}
int SettingsWindow::getListWidget()
{
    return ui->listWidget->currentRow();
}
