#include "cubesat.h"

Cubesat::Cubesat(double mass, double length)
{
    this->t = 0;
    this->mass = mass;
    this->length = length;
    this->speed = 0;
}

double Cubesat::getInertia(){
    double I = (mass/6)*pow(length,2);

    return I;
}
