#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QComboBox>
#include <satellite/wheel.h>
#include <satellite/cubesat.h>
#include <satellite/complexsat.h>
#include <ui/commandwindow.h>
#include <simulation/command.h>
#include "controller/controller.h"
#include "controller/pid.h"
#include "simulation/controlledsim.h"
#include "ui/trainwizzard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    //Simulation stuff comes right here
private:

    void readSat();
    Controller* ctrl;
    ControlledSim* simulation;
    Satellite* sat;
    double scaling;


public:
    Satellite* satellite;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void on_applyWheelBtn_clicked();

    //void on_applySatBtn_clicked();

    //void on_applyCompSatBtn_clicked();

    void on_addCmd_clicked();

    void on_startSimulation_clicked();

    void on_editCmd_clicked();

    void on_removeCmd_clicked();


    void on_train_clicked();

private:
    Ui::MainWindow *ui;
    CommandWindow *commandWindow;
    TrainWizzard *trainWizzard;
};
#endif // MAINWINDOW_H
