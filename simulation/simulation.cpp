#include "simulation.h"

Simulation::Simulation(Satellite* satellite, double duration)
{
    this->sat = satellite;
    this->duration = duration;
}

long Simulation::getSteps(){
    return steps;
}

Satellite* Simulation::getSatellite(){
    return sat;
}
