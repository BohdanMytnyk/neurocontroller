#include "commandwindow.h"
#include "ui_commandwindow.h"

CommandWindow::CommandWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CommandWindow)
{
    ui->setupUi(this);
}

CommandWindow::~CommandWindow()
{
    delete ui;
}

void CommandWindow::on_cmdOk_clicked()
{
    t = ui->timeEdit->text().toDouble();
    x = ui->xEdit->text().toDouble();
    return_ok = true;
    this->close();
}

void CommandWindow::on_cmdCancel_clicked()
{
    return_ok = false;
    this->close();
}
