#include "instruction.h"

Instruction::Instruction(double t, Wheel* wheel, double power){
    this->t = t;
    this->wheel = wheel;
    this->power = power;
}

void Instruction::execIfReady(double t){
    if(std::abs(this->t - t ) < 0.01) //executing the instruction if its time has come
        wheel->activateSpeedMode(power);
}
