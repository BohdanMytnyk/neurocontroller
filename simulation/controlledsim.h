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
    std::vector<double> t_values;
    std::vector<double> speed_values;
public:
    ControlledSim(Satellite* satellite, Controller* ctrl, double t );
    void putCommand(Command*);
    void run() override;

    std::vector<double> getT_values() const;
    std::vector<double> getSpeed_values() const;
};

#endif // CONTROLLEDSIM_H
