#include <vector>
#include <mpreal.h>
#include <cmath>
using namespace mpfr;

extern "C" 
{
mpreal f(int i, int n, const std::vector<mpreal> &x)
{
    switch (i) 
    {
        case 0: return 2*x[0]*x[0] + x[1] + x[2];
        case 1: return x[0] * x[1] - x[2] + 2;
        case 2: return (x[0] - x[1])*x[2];
    }
}

mpreal df(int i, int n, const std::vector<mpreal> &x)
{
    switch (i) 
    {
        case 0: return 4*x[0];
        case 1: return x[0];
        case 2: return x[0] - x[1];
    }
}
}
