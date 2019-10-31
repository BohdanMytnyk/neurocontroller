#include "simulation.h"

Simulation::Simulation(Satellite* satellite, double duration)
{
    this->sat = satellite;
    this->duration = duration;
    this->steps = static_cast<long>(duration/TIME_STEP);
}

long Simulation::getSteps(){
    return steps;
}

Satellite* Simulation::getSatellite(){
    return sat;
}
