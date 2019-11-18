#ifndef SAMPLEWIZZARD_H
#define SAMPLEWIZZARD_H

#include <QDialog>
#include <QFileDialog>
#include "controller/samplegenerator.h"
#if defined(Q_OS_LINUX)
   #include <QtConcurrentRun>
#elif defined(Q_OS_MACOS)
   #include <QtConcurrent/QtConcurrentRun>
#endif

namespace Ui {
class SampleWizzard;
}

class SampleWizzard : public QDialog
{
    Q_OBJECT

public:
    explicit SampleWizzard(QWidget *parent = nullptr, Satellite *sat = nullptr, double scaling =INPUT_SCALING);
    ~SampleWizzard();
    vector<Sample> getSamples();
//    void saveSamples();

private slots:
    void on_generate_clicked();

    void on_saveSamples_clicked();

private:
    Ui::SampleWizzard *ui;
    SampleGenerator* gen;
    void generate();
    Satellite *sat;
    vector<Sample> samples;
    double scaling;

};

#endif // SAMPLEWIZZARD_H
