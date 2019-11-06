#ifndef SIMULATION_H
#define SIMULATION_H
#include "../satellite/satellite.h"

#define TIME_STEP 0.001

class Simulation
{
    protected:
        Satellite* sat;
        double duration;
        long steps;
    public:
        Simulation();
        Simulation(Satellite* satellite, double duration);

        virtual void run() = 0;

        long getSteps();
        Satellite* getSatellite();
        void setDuration(double t);
};

#endif // SIMULATION_H
