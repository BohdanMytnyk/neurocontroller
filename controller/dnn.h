#ifndef DNN_H
#define DNN_H
#include <fstream>
#include <sstream>
#include "controller.h"
#include "sample.h"
#include "samplegenerator.h"
#include "../lib/MiniDNN/MiniDNN.h"

using namespace MiniDNN;
using namespace Eigen;

class DNN : public Controller
{
private:
    Network net;
    Optimizer* opt; //training optimizer from MiniDNN lib(for example, Gradient descent)
    int hiddenLayers, neurons; //num of hidden layers and of neurons per layer
    double inputScaling;

public:
    DNN();
    DNN(int hiddenLayers, int neurons);

    void setLRate(double a);
    void setInputScaling(double inputScaling);
    void setOptimizer(Optimizer *opt);

    void train(std::vector<Sample> samples, int batchSize, int epoch);
    double control(double desiredSpeed, double speed, double t) override;

    void save(const char* fileName);
    static DNN* construct(const char* fileName);
};

#endif // DNN_H
