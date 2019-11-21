#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../satellite/satellite.h"

class Controller
{
    protected:
    //parameters needed for controlling
        double dt, lastTime;
        double output;
    public:
        virtual double control(double desiredSpeed, double speed, double t) = 0;
        void reset(); //reset-function for starting controlling from the scratch
};

#endif // CONTROLLER_H
