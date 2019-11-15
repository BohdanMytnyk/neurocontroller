#include "samplewizzard.h"
#include "ui_samplewizzard.h"

SampleWizzard::SampleWizzard(QWidget *parent, Satellite *sat, double scaling) :
    QDialog(parent),
    ui(new Ui::SampleWizzard)
{
    ui->setupUi(this);
    this->sat = sat;
}

SampleWizzard::~SampleWizzard()
{
    delete ui;
}

void SampleWizzard::generate(){
    int n = ui->number->text().toInt();
    gen = new SampleGenerator(sat);
    samples = gen->generate(n);
    ui->generateStatus->setText("generated");
}

void SampleWizzard::on_generate_clicked()
{
    ui->generateStatus->setText("generating");
    QtConcurrent::run(this,&SampleWizzard::generate);
}

vector<Sample> SampleWizzard::getSamples()
{
    return samples;
}
