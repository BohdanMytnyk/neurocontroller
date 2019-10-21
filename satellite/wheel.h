#ifndef WHEEL_H
#define WHEEL_H

#include "QMetaType"
#include <cmath>

#define MODE_SPEED 0
#define MODE_TORQUE 1
#define T_MAX_TORQUE 0.5;



class Wheel
{
private:
    //attributes
    double mass, radius;
    double speed,desiredSpeed,maxSpeed;
    double torque,desiredTorque,maxTorque;
    double inertia;
    double angularMomentum;

    //controller modes
    void controllerSpeed(double dt);
    void controllerTorque(double dt);

    //controller attributes
    double Kp, sample_time, t;
    short CTRL_MODE = -1;

public:
    Wheel(double mass, double radius, double maxSpeed, double maxTorque);

    //wheel control function
    void activateSpeedMode(double power);
    void activateTorqueMode(double power);
    void update(double time_step);
    void reset();

    //getters
    double getMass();
    double getRadius();
    double getMaxSpeed();
    double getMaxTorque();
};


Q_DECLARE_METATYPE(Wheel*)
#endif // WHEEL_H
