#include <iostream>
#include "functions.h"
#include "gui.h"
#include <dlfcn.h>
using namespace std;

int main() 
{
    Fl_Window *window = new Fl_Window(1600,800 , "SIMPLENEWTON");
    window->color(FL_BLACK);
    Fl_Input *input = new Fl_Input(50, 10, 200, 30, "Input:");
    Fl_Output *output = new Fl_Output(50, 100, 200, 30, "Output:");
    Fl_Output *output_it = new Fl_Output(50, 140, 200, 30, "Output:");
    Fl_Button *btn1 = new Fl_Button(50, 50, 100, 40, "Button 1");
    Fl_Widget* widgets[3] = { input, output, output_it };
    btn1->callback(button_callback,widgets);


    mpreal::set_default_prec(80);
    void* handle = dlopen("./equations.so", RTLD_LAZY);
    F f =(F)dlsym(handle, "f");
    DF df =(DF)dlsym(handle, "df");
    FI fi =(FI)dlsym(handle, "fi");
    DFI dfi =(DFI)dlsym(handle, "dfi");
    vector<Interval<mpreal>> x = {{1,1}, {-1,-1}, {-1,-1}};
    Interval<mpreal> omega(0.8, 0.8);
    int it = 0;
    int st = 0;
    cout.precision(16);
    NewtonSimpleInterval(3, x, fi, dfi, omega, mpreal(1e-16), 150, it, st);
    cout << "Iterations: " << it << endl;
    cout << "Status: " << st << endl;
    string left, right;
    x[0].IEndsToStrings(left, right);
    cout << "x[0] = [" << left << ", " << right << "]" << endl;
    x[1].IEndsToStrings(left, right);
    cout << "x[1] = [" << left << ", " << right << "]" << endl;
    x[2].IEndsToStrings(left, right);
    cout << "x[2] = [" << left << ", " << right << "]" << endl;

    window->end();
    window->show();

    return Fl::run();
}