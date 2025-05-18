#include <iostream>
#include <mpreal.h>
#include <gmpxx.h>
#include "Interval.h"
#include "functions.h"
using namespace std;
using namespace interval_arithmetic;

void Hello()
{
    mpreal::set_default_prec(1024); // set precision to 256 bits

    mpreal a = "3.1415926535897932384626";
    mpreal b = "2.7182818284590452353602";
    Interval<mpreal> interval_a = { b, a };
    cout.precision(100); // set output precision to 100 digits
    cout << "Interval a width: " << interval_a.GetWidth() << endl;
}