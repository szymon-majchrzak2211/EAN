#include <iostream>
#include <mpreal.h>
#include <gmpxx.h>
#include "Interval.h"
#include "functions.h"
#include <dlfcn.h>
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
    int &st)
{
    if (n < 1 || mit < 1) {
        st = 1;
        return;
    }
    st = 0;
    it = 0;
    bool cond = false;
    vector<mpreal> x1(n);

    do {
        it++;
        if (it > mit) {
            st = 3;
            it--;
            break;
        } else {
            for (int i = 0; i < n; ++i) {
                mpreal d = df(i, n, x);
                if (d == 0.0) {
                    st = 2;
                    break;
                } else {
                    mpreal w = f(i, n, x);
                    x1[i] = x[i] - omega * w / d;
                }
            }

            if (st == 0) {
                cond = true;
                for (int i = 0; i < n; ++i) {
                    if (abs(x[i] - x1[i]) >= eps) {
                        cond = false;
                        break;
                    }
                }

                for (int i = 0; i < n; ++i) {
                    x[i] = x1[i];
                }
            }
        }
    } while (st == 0 && !cond);
}

bool isZero(const Interval<mpreal> &d) 
{
    if (d.a <= 0 && d.b >= 0) 
        return true;
    else 
        return false;
}

void NewtonSimpleInterval(
    int n, 
    vector<Interval<mpreal>> &x, 
    FI fi, 
    DFI dfi, 
    Interval<mpreal> omega, 
    mpreal eps, 
    int mit, 
    int &it, 
    int &st)
{
    if (n < 1 || mit < 1) {
        st = 1;
        return;
    }
    st = 0;
    it = 0;
    bool cond = false;
    vector<Interval<mpreal>> x1(n);

    do {
        it++;
        if (it > mit) {
            st = 3;
            it--;
            break;
        } else {
            for (int i = 0; i < n; ++i) {
                Interval<mpreal> d = dfi(i, n, x);
                if (isZero(d)) {
                    st = 2;
                    break;
                } else {
                    Interval<mpreal> w = fi(i, n, x);
                    x1[i] = x[i] - (omega * w / d);
                }
            }

            if (st == 0) {
                cond = true;
                for (int i = 0; i < n; ++i) {
                    if (abs(x1[i].a-x[i].a) >= eps || abs(x1[i].b-x[i].b) >= eps) {
                        cond = false;
                        break;
                    }
                }

                for (int i = 0; i < n; ++i) {
                    x[i] = x1[i];
                }
            }
        }
    } while (st == 0 && !cond);
}

void test(Interval<mpreal> &x) {
    x = x+x;
}