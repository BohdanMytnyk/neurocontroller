#ifndef SAMPLE_H
#define SAMPLE_H


class Sample
{
private:
    double dt, dw, u;
public:
    Sample();
    Sample(double dt, double dw, double u);

    double t();
    double w();
    double u_value();
};

#endif // SAMPLE_H
