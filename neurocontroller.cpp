#include "neurocontroller.h"
#include "ui_mainwindow.h"
#include "/Users/admin/Documents/neurocontroller/satellite/satellite.h"
#include "/Users/admin/Documents/neurocontroller/simulation/controlledsim.h"
#include "/Users/admin/Documents/neurocontroller/simulation/command.h"
#include "/Users/admin/Documents/neurocontroller/satellite/cubesat.h"
#include "/Users/admin/Documents/neurocontroller/controller/pid.h"

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

void MainWindow::on_applySatBtn_clicked()
{
    double mass = ui->cubesatMassEdit->text().toDouble();
    double length = ui->cubesatLengthEdit->text().toDouble();

    satellite = new Cubesat(mass,length);
}

void MainWindow::on_applyWheelBtn_clicked()
{
    double mass = ui->wheelMassEdit->text().toDouble();
    double radius = ui->wheelRadiusEdit->text().toDouble();
    double maxSpeed = ui->wheelMaxSpeedEdit->text().toDouble();
    double maxTorque = ui->wheelMaxTorqueEdit->text().toDouble();

    Wheel* wheel = new Wheel(mass,radius,maxSpeed,maxTorque);
    satellite->setWheel(wheel);
}


void MainWindow::on_applyCompSatBtn_clicked()
{
    double inertia = ui->ComplexSatInteria->text().toDouble();

    satellite = new ComplexSat(inertia);
}

