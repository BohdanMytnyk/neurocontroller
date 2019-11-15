#include "trainwizzard.h"
#include "ui_trainwizzard.h"

TrainWizzard::TrainWizzard(QWidget *parent, Satellite *sat, double scaling) :
    QDialog(parent),
    ui(new Ui::TrainWizzard)
{
    ui->setupUi(this);
    this->sat = sat;
}

TrainWizzard::~TrainWizzard()
{
    delete ui;
}

void TrainWizzard::on_generate_clicked()
{
    SampleWizzard* sampleWizzard = new SampleWizzard(this, sat, scaling);
    sampleWizzard->setWindowTitle("Sample Generator");
    sampleWizzard->setModal(true);
    sampleWizzard->exec();

    ui->samplesStatus->setText("Samples ready.");
    samples = sampleWizzard->getSamples();
}

void TrainWizzard::on_start_clicked()
{
    ui->dnnStatusLabel->setText("training, please wait");
    //getting the parameters from UI
    batchsize = ui->batch->text().toInt();
    epoches = ui->epoch->text().toInt();
    layers = ui->layers->text().toInt();
    neurons = ui->neurons->text().toInt();
    optIndex = ui->optimizer->currentIndex();
    lrate = ui->lrate->text().toDouble();
    QtConcurrent::run(this, &TrainWizzard::trainNetwork);
}

void TrainWizzard::trainNetwork(){
    //choose optimizer
    Optimizer* opt;
    switch (optIndex) {
        case(1):
            opt = new AdaGrad();
            break;
        case(2):
            opt = new SGD();
            break;
        default:
            opt = new RMSProp();
    }

    //constructing dnn for training
    dnn = new DNN(layers, neurons);

    dnn->setOptimizer(opt);
    dnn->setLRate(lrate);

    dnn->train(samples,batchsize,epoches);

    ui->dnnStatusLabel->setText("trained");
}

DNN* TrainWizzard::getDNN(){
    return dnn;
}

void TrainWizzard::on_load_clicked()
{
    QString qFileName = QFileDialog::getOpenFileName(this, tr("Import samples"), "", tr("Tables (*.csv);;All Files (*)"));
    samples = SampleGenerator::load(qFileName.toLocal8Bit().data());
    QFileInfo fi(qFileName);
    ui->samplesStatus->setText(fi.fileName() + " loaded.");
}

void TrainWizzard::on_cancel_clicked()
{
    this->close();
}

void TrainWizzard::on_saveSamples_clicked()
{
    QString qFileName = QFileDialog::getSaveFileName(this, tr("Export samples"), "", tr("Tables (*.csv);;All Files (*)"));
    if (qFileName.isEmpty()) return;
//    vector<Sample> sampleVec = getSamples();
//    SampleGenerator->save(samples, strcat(qFileName.toLocal8Bit().data(),static_cast<char*>(".csv")));
    SampleGenerator::save(samples, strcat(qFileName.toLocal8Bit().data(),static_cast<char*>(".csv")));
}
