#include "dnn.h"


DNN::DNN()
{
    this->inputScaling = INPUT_SCALING;
}

DNN::DNN(int hiddenLayers, int neurons) : DNN(){
    VerboseCallback call;
    net.set_callback(call);

    this->hiddenLayers = hiddenLayers;
    this->neurons = neurons;

    //add input layer
    net.add_layer(new FullyConnected<Identity>(2,neurons));

    //add hidden layers
    for(int i = 0; i < hiddenLayers; i++)
        net.add_layer(new FullyConnected<Sigmoid>(neurons,neurons));

    //add output layer
    net.add_layer(new FullyConnected<Identity>(neurons,1));
    net.set_output(new RegressionMSE());


    lastTime = 0;
}

void DNN::setLRate(double a){
    this->opt->setLRate(a);
}

void DNN::setInputScaling(double inputScaling)
{
    this->inputScaling = inputScaling;
}

void DNN::setOptimizer(Optimizer *opt)
{
    this->opt = opt;
}

void DNN::train(std::vector<Sample> samples, int batchSize, int epoch){
    VerboseCallback call;
    net.set_callback(call);

    //initialize network
    net.init(0, 0.01, 40);

    //init inputs and output matrices
    MatrixXd inputs(2,samples.size());
    MatrixXd outputs(1,samples.size());

    Sample s;

    for(size_t i = 0; i < samples.size(); i++){
        s = samples.at(i);

        inputs.col(static_cast<long>(i)) << s.t() , s.w();
        outputs.col(static_cast<long>(i)) << s.u_value();
    }

    //train the network
    net.fit(*opt, inputs, outputs, batchSize, epoch, 40);
}

double DNN::control(double desiredSpeed, double speed, double t){
    double dt = t - lastTime;
    if(dt < 0.5) return output;
    else{
        double error = desiredSpeed - speed;

        double scaledSpeed = inputScaling*error/dt;

        //feed the input
        MatrixXd input(2,1);

        input.col(0) << dt, scaledSpeed;

        //predict the output
        MatrixXd u = net.predict(input);

        lastTime = t;
        output = u(0,0);

        return output;
    }
}

