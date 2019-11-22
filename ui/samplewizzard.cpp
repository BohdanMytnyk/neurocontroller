#include "samplewizzard.h"
#include "ui_samplewizzard.h"
#include "trainwizzard.h"

SampleWizzard::SampleWizzard(QWidget *parent, Satellite *sat, double scaling) :
    QDialog(parent),
    ui(new Ui::SampleWizzard)
{
    ui->setupUi(this);
    this->sat = sat;
    samples_ready = false;
}

SampleWizzard::~SampleWizzard()
{
    delete ui;
}

void SampleWizzard::generate(){
    int n = ui->number->text().toInt();
    if(n != 0)
    {
        ui->generateStatus->setText("generating");
        gen = new SampleGenerator(sat);
        samples = gen->generate(n);
        ui->generateStatus->setText("generated");
        samples_ready = true;
    }
}

void SampleWizzard::on_generate_clicked()
{
    QtConcurrent::run(this,&SampleWizzard::generate);
}

vector<Sample> SampleWizzard::getSamples()
{
    return samples;
}
