#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "../satellite/wheel.h"


class Instruction
{
    private:
         double t;
         Wheel* wheel;
         double power;
    public:
         Instruction(double t, Wheel* wheel, double power);
         void execIfReady(double t);
};

#endif // INSTRUCTION_H
