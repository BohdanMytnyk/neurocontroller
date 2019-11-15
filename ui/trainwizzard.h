#ifndef TRAINWIZZARD_H
#define TRAINWIZZARD_H
#if defined(Q_OS_LINUX)
   #include <QtConcurrentRun>
#elif defined(Q_OS_MACOS)
   #include <QtConcurrent/QtConcurrentRun>
#endif
#include <QDialog>
#include "samplewizzard.h"
#include "controller/dnn.h"
#include "satellite/satellite.h"

namespace Ui {
class TrainWizzard;
}

class TrainWizzard : public QDialog
{
    Q_OBJECT

public:
    explicit TrainWizzard(QWidget *parent = nullptr, Satellite* sat = nullptr, double scaling = INPUT_SCALING);
    ~TrainWizzard();
    DNN* getDNN();
    void setLabel();
    void trainNetwork();

private slots:
    void on_generate_clicked();

    void on_start_clicked();

private:
    Ui::TrainWizzard *ui;
    Satellite* sat;
    DNN* dnn;
    vector<Sample> samples;

    int batchsize, epoches, layers, neurons, optIndex;
    double lrate;
    double scaling;
};

#endif // TRAINWIZZARD_H
