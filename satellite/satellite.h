#ifndef SATELLITE_H
#define SATELLITE_H

#include "wheel.h"

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

//        double roll();
//        double pitch();
//        double yaw();

        void update(double time_step);
        void reset();

};

#endif // SATELLITE_H
