#include "controlledsim.h"

std::vector<double> ControlledSim::getT_values() const
{
    return t_values;
}

std::vector<double> ControlledSim::getSpeed_values() const
{
    return speed_values;
}

ControlledSim::ControlledSim(Satellite* sat, Controller* ctrl, double t) : Simulation(sat,t)
{
    this->sat = sat;
    this->ctrl = ctrl;
}

void ControlledSim::putCommand(Command* cmd)
{
    commands.push_back(cmd);
}

void ControlledSim::run()
{
    //starting the simulation
    int index = 0;
    for(double t = 0.0; t < duration; t+=TIME_STEP)
    {
        //writing an actual time and speed for the future plotting
        t_values.push_back(t);
        speed_values.push_back(sat->getSpeed());
        index++;

        //search for a valid command
        for(size_t i = 0; i < commands.size(); i++)
            desiredSpeed = commands.at(i)->acceptIfReady(desiredSpeed,t);

        //using the controller to predict the next output
        double currentSpeed = sat->getSpeed();
        ctrl_output = ctrl->control(desiredSpeed, currentSpeed, t);

        //apply the controllers output to the reaction wheels
        sat->getWheel()->activateTorqueMode(ctrl_output);

        //update the satellite
        sat->update(TIME_STEP);
    }
}




