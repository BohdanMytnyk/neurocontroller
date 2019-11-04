#include "instructedsim.h"

InstructedSim::InstructedSim(Satellite* sat, double t) : Simulation(sat, t)
{
    this->sat = sat;
    this->duration = t;
}

void InstructedSim::putInstruction(Instruction *inst){
    instructions.push_back(inst);
}

void InstructedSim::run(){
    //starting the simulation
    for(double t = 0; t < duration; t+=TIME_STEP){

        //finding the ready instruction and executing it
        for(size_t i = 0; i < instructions.size(); i++)
            instructions.at(i)->execIfReady(t);

        //updating the satellite
        sat->update(TIME_STEP);
    }
}
