#include <iostream>
#include "functions.h"
#include <dlfcn.h>
using namespace std;

int main() 
{
    mpreal::set_default_prec(80);
    void* handle = dlopen("./equations.so", RTLD_LAZY);
    F f =(F)dlsym(handle, "f");
    DF df =(DF)dlsym(handle, "df");
    vector<mpreal> x = {1, -1, -1};
    int it = 0;
    int st = 0;
    cout.precision(16);
    NewtonSimpleNormal(
        3, 
        x,
        f, 
        df, 
        mpreal(0.8), 
        mpreal(1e-16), 
        150, 
        it, 
        st
    );
    cout << "Newton's method completed with status: " << st << " after " << it << " iterations." << endl;
    cout << "Final values: ";
    for (const auto& val : x) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}