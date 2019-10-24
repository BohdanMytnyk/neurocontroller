#ifndef PID_H
#define PID_H
#define BOUND 1

#include "controller.h"

class PID : Controller
{
    private:
        double Kp, Ki, Kd; // P,I,D
        double u; // output
        double S; // integral
        double lastError; // previous measurement error
        double lastDesiredSpeed; // previous desired speed

    public:
        PID(double Kp, double Ki, double Kd);
        double control(double desiredSpeed, double speed, double t) override;
};

#endif // PID_H
