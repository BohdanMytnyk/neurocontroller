#ifndef UTILS
#define UTILS

#endif // UTILS

#include<random>

#define DISTURBANCE_FREQUENCZ 0.02
#define DISTURBANCE_PERCENTAGE 0.01

static double dist_freq = DISTURBANCE_FREQUENCZ;
static double dist_perc = DISTURBANCE_PERCENTAGE;

static std::uniform_real_distribution<double> unif(-0.001, 0.001);
static std::default_random_engine re;

inline double disturb(double speed, double t){
    double sin_t = sin(2 * M_PI * dist_freq * t);
    return speed + dist_perc * speed * sin_t;
}

inline double applyNoise(double w){
    double noise = unif(re);
    return w + noise * w;
}
