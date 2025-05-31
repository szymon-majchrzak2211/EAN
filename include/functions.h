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
typedef Interval<mpreal> (*FI)(int i, int n, const std::vector<Interval<mpreal>> &x);
typedef Interval<mpreal> (*DFI)(int i, int n, const std::vector<Interval<mpreal>> &x);

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

void NewtonSimpleInterval(
    int n, 
    vector<Interval<mpreal>> &x, 
    FI f, 
    DFI df, 
    Interval<mpreal> omega, 
    mpreal eps, 
    int mit, 
    int &it, 
    int &st
);

void test(Interval<mpreal> &x);


#endif