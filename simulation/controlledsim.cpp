#include "controlledsim.h"

ControlledSim::ControlledSim(Satellite* sat, Controller* ctrl, double t) : Simulation(sat,t)
{
    this->sat = sat;
    this->ctrl = ctrl;
    this->t = new double[steps + 1];
    this->speed_values = new double[steps + 1];
}

void ControlledSim::putCommand(Command* cmd)
{
    commands.push_back(cmd);
}

void ControlledSim::run()
{
    //Simulation start
    int index = 0;
    for(double t = 0.0; t < duration; t+=TIME_STEP)
    {
        //Write status of sat in array
        this->t[index] = t;
        this->speed_values[index] = sat->getSpeed();
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




