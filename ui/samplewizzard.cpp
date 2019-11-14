#include "samplewizzard.h"
#include "ui_samplewizzard.h"

SampleWizzard::SampleWizzard(QWidget *parent, Satellite *sat, double scaling) :
    QDialog(parent),
    ui(new Ui::SampleWizzard)
{
    ui->setupUi(this);
}

SampleWizzard::~SampleWizzard()
{
    delete ui;
}
