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

#if defined(Q_OS_LINUX)
   #define PATH_DEPTH 1
#elif defined(Q_OS_MACOS)
   #define PATH_DEPTH 4
#endif



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
    DNN* dnn; //pointer for dnn if it exists
    ControlledSim* simulation;
    Satellite* sat;
    double scaling;
    QString * netFile;
    int path_depth;


public:
    Satellite* satellite;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_addCmd_clicked();

    void on_startSimulation_clicked();

    void on_editCmd_clicked();

    void on_removeCmd_clicked();


    void on_train_clicked();

    void on_loadNet_clicked();

    void on_saveDnn_clicked();

    void formSim();

    void on_actionPID_sim_triggered();

    void on_actionDNN_sim_triggered();

private:
    Ui::MainWindow *ui;
    CommandWindow *commandWindow;
    TrainWizzard *trainWizzard;
};
#endif // MAINWINDOW_H
