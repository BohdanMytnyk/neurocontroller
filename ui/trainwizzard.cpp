#include "trainwizzard.h"
#include "ui_trainwizzard.h"

TrainWizzard::TrainWizzard(QWidget *parent, Satellite *sat, double scaling) :
    QDialog(parent),
    ui(new Ui::TrainWizzard)
{
    ui->setupUi(this);
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
}
