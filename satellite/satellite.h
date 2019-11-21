#ifndef SATELLITE_H
#define SATELLITE_H

#include "wheel.h"
#include "../utils.h"

class Satellite{
    protected:
        double speed;
        Wheel* wheel;
        double t;

    public:
        virtual double getInertia() = 0;
        double getSpeed();

        void setWheel(Wheel* wheel);
        Wheel* getWheel();

        void update(double time_step);
        void reset();

};

#endif // SATELLITE_H
