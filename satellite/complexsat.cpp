#include "complexsat.h"

ComplexSat::ComplexSat(double inertia)
{
    this->t = 0;
    this->inertia = inertia;
    this->speed = 0;
}

double ComplexSat::getInertia()
{
    return inertia;
}
