#include "neurocontroller.h"
#include "ui_mainwindow.h"
#include "satellite/wheel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_applyWheelBtn_clicked()
{
    double mass = ui->wheelMassEdit->text().toDouble();
    double radius = ui->wheelRadiusEdit->text().toDouble();
    double maxSpeed = ui->wheelMaxSpeedEdit->text().toDouble();
    double maxTorque = ui->wheelMaxTorqueEdit->text().toDouble();

    wheel = new Wheel(mass,radius,maxSpeed,maxTorque);
}
