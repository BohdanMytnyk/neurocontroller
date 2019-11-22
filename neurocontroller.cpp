#include "neurocontroller.h"
#include "ui_mainwindow.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    path_depth = PATH_DEPTH;

    // setup the graph
    ui->qPlot->addGraph();
    ui->qPlot->graph(0)->setPen(QPen(Qt::red));
    ui->qPlot->graph(0)->setName("speed");
    ui->qPlot->legend->setVisible(true);
    QFont legendFont = font(); // MainWindow's font
    legendFont.setPointSize(9); // make it smaller
    ui->qPlot->legend->setFont(legendFont);
    ui->qPlot->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startSimulation_clicked()
{
    ui->statusLabel->setText("simulation...");
    ui->statusLabel->repaint();

    //get Satellite
    readSat();

    //Construct simulation (get controller)
    double duration = ui->durationEdit->text().toDouble();
    if (ui->tab_sim->currentIndex() == 0){
        ctrl = new PID(ui->kp->text().toDouble(), ui->ki->text().toDouble(), ui->kd->text().toDouble());
    } else if (!netFile->isEmpty()){
        ctrl = DNN::construct(netFile->toLocal8Bit().data());
    } else {
        dnn->reset();
        ctrl = dnn;
    }

    simulation = new ControlledSim(satellite, ctrl, duration);
    ui->statusLabel->setText("");

    //get commands   cmdComboBox
    for (int i=0; i < ui->cmdComboBox->count(); i++){
        simulation->putCommand(ui->cmdComboBox->itemData(i).value<Command*>());
    }

    //run the simmulation
    simulation->run();
    QMessageBox::information(this, "Simulation status", "Simulation finished");
    ui->statusLabel->setText("");
    ui->statusLabel->repaint();

    //Draw the plot
    int n = simulation->getSteps();
    std::vector<double> t_values = simulation->getT_values();
    std::vector<double> speed_values = simulation->getSpeed_values();

    QVector<double> t(n), speed(n); // get values time and speed
    for (int i=0; i<n; i++){
        t[i] = t_values[i];
        speed[i] = speed_values[i];
    }

    // set values for drowing plot
    ui->qPlot->graph(0)->setData(t, speed);
    ui->qPlot->xAxis->setLabel("t");
    ui->qPlot->yAxis->setLabel("speed");
    ui->qPlot->rescaleAxes();
    ui->qPlot->replot();
}


void MainWindow::readSat()
{
    if (ui->tabWidget->currentIndex() == 0) { // cubesat
        double massCube = ui->cubesatMassEdit->text().toDouble();
        double lenght = ui->cubesatLengthEdit->text().toDouble();
        satellite = new Cubesat(massCube, lenght);
    } else {                                  // complexsat
        double inertia;
        inertia = ui->ComplexSatInteria->text().toDouble();
        satellite = new ComplexSat(inertia);
    }

    // get weel
    double mass = ui->wheelMassEdit->text().toDouble();
    double radius = ui->wheelRadiusEdit->text().toDouble();
    double maxSpeed = ui->wheelMaxSpeedEdit->text().toDouble();
    double maxTorque = ui->wheelMaxTorqueEdit->text().toDouble();

    Wheel* wheel = new Wheel(mass,radius,maxSpeed,maxTorque);
    satellite->setWheel(wheel);
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
        double w = commandWindow->w;

        Command* cmd = new Command(w, t);
        QString str = QString("%1s, %2rad/s").arg(t).arg(w);
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
        double w = commandWindow->w;
        cmd = new Command(w, t);
        QString str = QString("%1s, %2rad/s").arg(t).arg(w);
        ui->cmdComboBox->addItem(str, QVariant::fromValue(cmd));
    }
}

void MainWindow::on_removeCmd_clicked()
{
    ui->cmdComboBox->removeItem(ui->cmdComboBox->currentIndex());
}

void MainWindow::on_train_clicked()
{
    readSat();
    trainWizzard = new TrainWizzard(this, satellite, scaling);
    trainWizzard->setWindowTitle("DNN Training Wizzard");
    trainWizzard->setModal(true);
    trainWizzard->exec();

    //setting the DNN when it's trained
    netFile = new QString("");
    dnn = trainWizzard->getDNN();
    ui->dnnStatus->setText("DNN loaded.");
    ui->saveDnn->setEnabled(true);
}

void MainWindow::on_loadNet_clicked()
{

        netFile = new QString (QFileDialog::getOpenFileName(this, tr("Import network"), "", tr("DNN files (*.dnn);;All Files (*)")));
        if (netFile->isEmpty()) return;
        DNN::construct(netFile->toLocal8Bit().data());

        char* netFileTmp = netFile->toLocal8Bit().data();
        QFileInfo fi(netFileTmp);

        ui->dnnStatus->setText(fi.fileName());
        ui->saveDnn->setEnabled(true);

}

void MainWindow::on_saveDnn_clicked()
{
    QString qFileName = QFileDialog::getSaveFileName(this, tr("Import network"), "", tr("DNN files (*.dnn);;All Files (*)"));
    if(qFileName.isEmpty()) return;

    dnn->save(strcat(qFileName.toLocal8Bit().data(),(".dnn")));
}

void MainWindow::formSim(){
    this->ui->cubesatMassEdit->setText("500");
    this->ui->cubesatLengthEdit->setText("1");

    this->ui->wheelMassEdit->setText("9.5");
    this->ui->wheelMaxSpeedEdit->setText("7300");
    this->ui->wheelRadiusEdit->setText("0.347");
    this->ui->wheelMaxTorqueEdit->setText("0.17");

    this->ui->durationEdit->setText("60");

    Command* cmd = new Command(0.04, 0);
    QString str = QString("%1s, %2rad/s").arg("0").arg("0.04");
    ui->cmdComboBox->addItem(str, QVariant::fromValue(cmd));
}

void MainWindow::on_actionPID_sim_triggered()
{
    formSim();
    ui->tab_sim->setCurrentIndex(0);

    this->ui->kp->setText("500");
    this->ui->ki->setText("0");
    this->ui->kd->setText("20");
}

void MainWindow::on_actionDNN_sim_triggered()
{
    formSim();
    ui->tab_sim->setCurrentIndex(1);
    string path = QCoreApplication::applicationDirPath().toStdString();

    while(true){
        if(path[path.length()-1] == '/')
            path_depth -= 1;

        path.erase(path.length()-1);

        if(path_depth == 0){
            path_depth = PATH_DEPTH;
            break;
        }
    }

    if(path.substr(path.length()-15, 15) != "neurocontroller")
        path+= "/neurocontroller";

    netFile = new QString(QString::fromStdString(path) + "/sampleDNN.dnn");
    ui->dnnStatus->setText("Sample DNN loaded.");
}
