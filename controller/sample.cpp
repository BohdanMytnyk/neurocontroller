#include "sample.h"

Sample::Sample(double dt, double dw, double u){
    this->dt = dt;
    this->dw = dw;
    this->u = u;
}

double Sample::t(){
    return dt;
}

double Sample::w(){
    return dw;
}

double Sample::u_value(){
    return u;
}
