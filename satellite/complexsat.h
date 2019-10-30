#ifndef COMPLEXSAT
#define COMPLEXSAT

#include "satellite.h"

class ComplexSat : public Satellite
{
private:
    double inertia;

public:
    ComplexSat(double inertia);
    double getInertia() override;

};

#endif // COMPLEXSAT

