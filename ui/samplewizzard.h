#ifndef SAMPLEWIZZARD_H
#define SAMPLEWIZZARD_H

#include <QDialog>
#include <QFileDialog>
//#include <QtConcurrent>
#include "controller/samplegenerator.h"

namespace Ui {
class SampleWizzard;
}

class SampleWizzard : public QDialog
{
    Q_OBJECT

public:
    explicit SampleWizzard(QWidget *parent = nullptr, Satellite *sat = nullptr, double scaling =INPUT_SCALING);
    ~SampleWizzard();
//    vector<Sample>

private:
    Ui::SampleWizzard *ui;
    SampleGenerator gen;
    Satellite *sat;
    double scaling;
};

#endif // SAMPLEWIZZARD_H
