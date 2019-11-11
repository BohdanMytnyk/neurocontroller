#ifndef COMMAND_H
#define COMMAND_H
#include <cmath>
#include "QMetaType"

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

Q_DECLARE_METATYPE(Command*)

#endif // COMMAND_H
