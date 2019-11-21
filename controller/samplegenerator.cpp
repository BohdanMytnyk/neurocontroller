#include "samplegenerator.h"

SampleGenerator::SampleGenerator()
{
    w_distr = uniform_real_distribution<double>(-SPEED_RANGE, SPEED_RANGE);
    t_distr = uniform_real_distribution<double>(0.5, TIME_RANGE);
    u_distr = uniform_real_distribution<double>(-SIGNAL_RANGE, SIGNAL_RANGE);

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

    for(int i = 0; i < numOfSamples/100*4; i++){
        //generate random time interval
        dt = round(t_distr(random) * 1000.0)/1000.0;

        sim.setDuration(dt);

        //generate 0 controller output
        double u = 0;

        //apply output u to the wheel of a satellite
        sat->getWheel()->activateTorqueMode(u);

        //calculate dw
        double dw = sat->getSpeed()/dt;

        //create sample
        Sample* sample = new Sample(dt,round(inputScaling*dw),u);

        samples.push_back(*sample);

        sat->reset();
    }

    return samples;
}


//save the samples into a file
void SampleGenerator::save(vector<Sample> &samples, const char *fileName){
    ofstream out(fileName);
    Sample s;

    for(size_t i = 0; i < samples.size(); i++){
        s = samples.at(i);
        out << s.t() << ";" << s.w() << ";" << s.u_value() << endl;
    }

    out.flush();
}

//save the samples from a file
vector<Sample> SampleGenerator::load(const char *filename){
    vector<Sample> samples = *(new vector<Sample>());

    ifstream file(filename);
    string line;

    while(getline(file,line)){
        stringstream linestr(line);
        string item;

        //read all parameters
        getline(linestr, item, ';');
        double dt = QString(item.c_str()).toDouble();

        getline(linestr, item, ';');
        double dw = QString(item.c_str()).toDouble();

        getline(linestr, item, ';');
        double u = QString(item.c_str()).toDouble();


        samples.push_back(*(new Sample(dt, dw, u)));
    }

    return samples;
}


