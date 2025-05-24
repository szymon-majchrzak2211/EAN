#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <mpreal.h>
#include <gmpxx.h>
#include "Interval.h"


using namespace std;
using namespace interval_arithmetic;
using namespace mpfr;


typedef mpreal (*F)(int i, int n, const std::vector<mpreal> &x);
typedef mpreal (*DF)(int i, int n, const std::vector<mpreal> &x);

void Hello();
void NewtonSimpleNormal(
    int n, 
    vector<mpreal> &x, 
    F f, 
    DF df, 
    mpreal omega, 
    mpreal eps, 
    int mit, 
    int &it, 
    int &st
);

#endif