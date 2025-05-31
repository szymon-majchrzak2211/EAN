#include "gui.h"
#include "functions.h"
#include <string>
#include <dlfcn.h>


void button_callback(Fl_Widget* widget, void* data) 
{
    void* handle = dlopen("./equations.so", RTLD_LAZY);
    F f =(F)dlsym(handle, "f");
    DF df =(DF)dlsym(handle, "df");
    auto** widgets = static_cast<Fl_Widget**>(data);
    Fl_Input* input = static_cast<Fl_Input*>(widgets[0]);
    Fl_Output* output = static_cast<Fl_Output*>(widgets[1]);
    Fl_Output* output_it =static_cast<Fl_Output*>(widgets[2]);
    vector<mpreal> x = {input->value(), -1, -1};
    int it = 0;
    int st = 0;
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
    string xs = x[0].toString();
    const char* xc = xs.c_str();
    string its = to_string(it);
    const char* itc = its.c_str();
    output->value(xc); 
    output_it->value(itc);
}