#include "wheel.h"


Wheel::Wheel(double mass, double radius, double maxSpeed, double maxTorque)
{
    this->mass = mass;
    this->radius = radius;
    this->maxSpeed = maxSpeed*2*M_PI*1.0/60.0;
    this->maxTorque = maxTorque;
    this->speed = 0;
    this->inertia = 0.5*mass*pow(radius,2);
    this->angularMomentum = speed*inertia;
    Kp = 0.0325; sample_time = 0.01; t = 0;
}

double Wheel::getAngularMomentum()
{
    angularMomentum = speed*inertia;
    return angularMomentum;
}

//power is a value in percents of max speed to take desired speed
void Wheel::activateSpeedMode(double power){
    CTRL_MODE = MODE_SPEED;

    if(power > 1)
        power = 1;
    else if(power < -1)
        power = -1;
    desiredSpeed = power*maxSpeed;
}

//power is a value in percents of max torque to take desired torque
void Wheel::activateTorqueMode(double power){
    CTRL_MODE = MODE_TORQUE;

    if(power > 1)
        power = 1;
    else if(power < -1)
        power = -1;
    desiredTorque = power*maxTorque;
}

double Wheel::getInertia() const
{
    return inertia;
}

void Wheel::controllerSpeed(double time_step){
    t+=time_step;

    if(sample_time >= t){
        double error = desiredSpeed - speed;
        desiredTorque = Kp*error;

        if(desiredTorque<-maxTorque)
            desiredTorque = -maxTorque;
        else if(desiredTorque>maxTorque)
            desiredTorque = maxTorque;

        t = 0;
    }

    controllerTorque(time_step);
}

void Wheel::controllerTorque(double time_step){
    if( desiredTorque > torque)
        torque += time_step* maxTorque /T_MAX_TORQUE
    else if( desiredTorque < torque)
        torque -= time_step* maxTorque /T_MAX_TORQUE

    if( torque < -maxTorque)
        torque = -maxTorque;
    else if( torque > maxTorque)
        torque = maxTorque;

}

//updating of the wheel every step of time
void Wheel::update(double time_step){
    switch(CTRL_MODE)
    {
        case MODE_SPEED:
            controllerSpeed(time_step);
            break;
        case MODE_TORQUE:
            controllerTorque(time_step);
            break;
    }

    double a = torque/inertia; //finding the acceleration
    speed += a*time_step; // w = a*dt

    if(speed > maxSpeed)
        speed = maxSpeed;
    else if(speed < -maxSpeed)
        speed = -maxSpeed;
}

void Wheel::reset(){
    speed = 0;
    desiredSpeed = 0;
    torque = 0;
    desiredTorque = 0;
}


double Wheel::getMass(){
    return mass;
}

double Wheel::getRadius(){
    return radius;
}

double Wheel::getMaxSpeed()
{
    return maxSpeed;
}

double Wheel::getMaxTorque()
{
    return maxTorque;
}

