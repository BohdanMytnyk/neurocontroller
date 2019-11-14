#ifndef TRAINWIZZARD_H
#define TRAINWIZZARD_H

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

private slots:
    void on_generate_clicked();

private:
    Ui::TrainWizzard *ui;
    Satellite* sat;

    int batchsize, epochs, layers, neurons, optIndex;
    double lrate;
    double scaling;
};

#endif // TRAINWIZZARD_H
