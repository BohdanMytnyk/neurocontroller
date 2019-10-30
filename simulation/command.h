#ifndef COMMAND_H
#define COMMAND_H
#include <cmath>


class Command{
    private:
        double desiredSpeed;
        double t;
    public:
        Command(double desiredSpeed, double t);
        double getDesiredSpeed();
        double getTime();
        double acceptIfReady(double oldSpeedValue, double t);
};


#endif // COMMAND_H
