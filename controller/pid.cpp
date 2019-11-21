#include "pid.h"

PID::PID(double Kp, double Ki, double Kd)
{
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;

    S = 0;
    lastError = 0;
    lastDesiredSpeed = 0;
    lastTime = 0;
}

double PID::control(double desiredSpeed, double speed, double t){
    double dt = t - lastTime;

    if(dt < 0.5) return output;
    else{

        double error = desiredSpeed - speed;

        //calculating integral part if Ki exists
        if(Ki != 0.0) {
            if(-BOUND< u && u <BOUND ) S += Ki*error*dt;
            else if(u < -BOUND) S = -BOUND;
            else if(u > BOUND) S = BOUND;
        }


        //calculating deriavative of measurement
        double dError = (desiredSpeed - lastDesiredSpeed)/dt - (error - lastError)/dt;

        //calculating the output u
        u = Kp*error + S + Kd*dError;

        if(u < -BOUND) u = -BOUND;
        else if(u > BOUND) u = BOUND;


        //remember for the next steps
        output = u;
        lastTime = t;
        lastError = error;
        lastDesiredSpeed = desiredSpeed;

        return output;
    }

}
