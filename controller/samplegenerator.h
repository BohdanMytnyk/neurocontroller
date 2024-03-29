#ifndef SAMPLEGENERATOR_H
#define SAMPLEGENERATOR_H

#include "sample.h"
#include "../satellite/satellite.h"
#include "../simulation/instructedsim.h"
#include <QObject>
#include <fstream>
#include <sstream>

#define SPEED_RANGE 0.1
#define TIME_RANGE 5
#define SIGNAL_RANGE 1
#define INPUT_SCALING 5000

using namespace std;


class SampleGenerator : QObject
{
    Q_OBJECT

private:
    Satellite* sat;

    //distributions of parameters for randomization
    uniform_real_distribution<double> w_distr;
    uniform_real_distribution<double> t_distr;
    uniform_real_distribution<double> u_distr;

    default_random_engine random;

    double inputScaling;

public:
    SampleGenerator();
    SampleGenerator(Satellite* sat);

    double getInputScaling();
    void setInputScaling(double inputScaling);

    vector<Sample> generate(int numOfSamples);
    static void save(vector<Sample> &samples, const char *fileName);
    static vector<Sample> load(const char *filename);
};

#endif // SAMPLEGENERATOR_H
