#include "samplegenerator.h"

SampleGenerator::SampleGenerator()
{
    w_distr = uniform_real_distribution<double>(-SPEED_RANGE, SPEED_RANGE);
    t_distr = uniform_real_distribution<double>(0.5, TIME_RANGE);
    u_distr = uniform_real_distribution<double>(-SIGNAL_RANGE, SIGNAL_RANGE);

    gen_stopped = false;

    inputScaling = INPUT_SCALING;
}

SampleGenerator::SampleGenerator(Satellite *sat) : SampleGenerator()
{
    this->sat = sat;
}

double SampleGenerator::getInputScaling()
{
    return inputScaling;
}

void SampleGenerator::setInputScaling(double inputScaling)
{
    this->inputScaling = inputScaling;
}

vector<Sample> SampleGenerator::generate(int numOfSamples){
    vector<Sample> samples = *(new vector<Sample>());

    double dt;
    InstructedSim sim(sat, 0);

    for(int i = 0; i < numOfSamples; i++){
        if (gen_stopped) break;

        //generate random time interval
        dt = round(t_distr(random) * 1000.0)/1000.0;

        sim.setDuration(dt);

        //generate random controller output
        double u = round(u_distr(random) * 1000.0)/1000.0;

        //apply output u to the wheel of a satellite
        sat->getWheel()->activateTorqueMode(u);

        //run the sim
        sim.run();

        //calculate dw
        double dw = sat->getSpeed()/dt;

        //create sample
        Sample* sample = new Sample(dt,round(inputScaling*dw),u);

        samples.push_back(*sample);

        sat->reset();
    }
    gen_stopped = false;

    return samples;
}
