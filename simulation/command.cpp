#include "command.h"

Command::Command(double desiredSpeed,double t){
    this->desiredSpeed = desiredSpeed;
    this->t = t;
}

double Command::getDesiredSpeed(){
    return desiredSpeed;
}

double Command::getTime(){
    return t;
}

double Command::acceptIfReady(double oldSpeedValue, double t){
    if(abs(this->t - t) < 0.01)
        return desiredSpeed;
    return oldSpeedValue;
}
