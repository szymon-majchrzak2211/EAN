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
void* handle = dlopen("./equations.so", RTLD_LAZY);
F f =(F)dlsym(handle, "f");
DF df =(DF)dlsym(handle, "df");

void Hello()
{
    vector<mpreal> x = {1.0, 2.83298392392, 3.0};
    mpreal result = f(0, 3, x);
    cout.precision(100);
    cout << "Wynik funkcji f(0, 3, x): " << result << endl;
}

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