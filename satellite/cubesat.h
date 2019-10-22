#ifndef CUBESAT_H
#define CUBESAT_H

#include "satellite.h"


class Cubesat: public Satellite
{
    private:
        double mass;
        double length;
    public:
        Cubesat(double mass, double length);
        double getInertia() override;
};

#endif // CUBESAT_H
