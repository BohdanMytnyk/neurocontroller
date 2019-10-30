#ifndef CONTROLLEDSIM_H
#define CONTROLLEDSIM_H

#include "command.h"
#include "simulation.h"
#include "../controller/controller.h"
#include <vector>


class ControlledSim :public Simulation
{
private:
    Controller * ctrl;
    double ctrl_output;
    double desiredSpeed;
    std::vector<Command*> commands;
    double * t;
    double * speed_values;
public:
    ControlledSim(Satellite* satellite, Controller* ctrl, double t );
    void putCommand(Command*);
    void run() override;

};

#endif // CONTROLLEDSIM_H
