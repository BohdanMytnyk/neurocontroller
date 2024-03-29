#include "satellite.h"

double Satellite::getSpeed(){
    return speed;
}

void Satellite::setWheel(Wheel *wheel){
    this->wheel = wheel;
}

Wheel* Satellite::getWheel(){
    return wheel;
}

//updating satellite condition
void Satellite::update(double time_step){
    t+=time_step;

    double inertia = this->getInertia(); // I

    double angularMomentum = wheel->getAngularMomentum(); // L

    speed = angularMomentum/inertia; // L = I*w  =>  w = L/I

    //applying noise to the speed
    speed = disturb(speed, t);
    speed = applyNoise(speed);

    //updating wheel condition
    wheel->update(time_step);
}

void Satellite::reset(){
    speed = 0;
    t = 0;
    this->getWheel()->reset();
}


