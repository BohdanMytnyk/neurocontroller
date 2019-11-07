#include "neurocontroller.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_addCmd_clicked()
{
    commandWindow = new CommandWindow(this);
    commandWindow->setWindowTitle("New Command");
    commandWindow->setModal(true);
    commandWindow->exec();
    if (commandWindow->return_ok)
    {
        //ui->cmdComboBox->removeItem(ui->cmdComboBox->currentIndex());
        double t = commandWindow->t;
        double x = commandWindow->x;

        Command* cmd = new Command(t, x);
        QString str = QString("%1s, %2rad/s").arg(t).arg(x);
        ui->cmdComboBox->addItem(str, QVariant::fromValue(cmd));
    }
}

void MainWindow::on_editCmd_clicked()
{
    Command * cmd = ui->cmdComboBox->itemData(ui->cmdComboBox->currentIndex()).value<Command*>(); //currentData().value<Command*>();
    if (cmd == nullptr) return;
    commandWindow = new CommandWindow(this, cmd->getTime(), cmd->getDesiredSpeed());
    commandWindow->setWindowTitle("Edit Command");
    commandWindow->setModal(true);
    commandWindow->exec();
    if (commandWindow->return_ok)
    {
        ui->cmdComboBox->removeItem(ui->cmdComboBox->currentIndex());
        double t = commandWindow->t;
        double x = commandWindow->x;
        cmd = new Command(t, x);
        QString str = QString("%1s, %2rad/s").arg(t).arg(x);
        ui->cmdComboBox->addItem(str, QVariant::fromValue(cmd));
    }
}

void MainWindow::on_removeCmd_clicked()
{
    ui->cmdComboBox->removeItem(ui->cmdComboBox->currentIndex());
}
