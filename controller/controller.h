#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../satellite/satellite.h"

class Controller
{
    protected:
        double dt, lastTime;
        double output;
    public:
        virtual double control(double desiredSpeed, double speed, double t) = 0;
        void reset();
};

#endif // CONTROLLER_H
