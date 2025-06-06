#include <iostream>
#include "functions.h"
#include "gui.h"
#include <dlfcn.h>
using namespace std;

int main() 
{
    Fl_Window *window = new Fl_Window(1600,800 , "SIMPLENEWTON");
    window->begin();
    window->position(100, 100);
    window->color(FL_YELLOW);

    Fl_Choice *choice = new Fl_Choice(50, 10, 100, 30, "Rodzaj arytmetyki:");
    choice->add("Rzeczywiste|Przedziałowe punktowe|Przedziałowe");


    Fl_Input *input_number_equations = new Fl_Input(400, 10, 200, 30, "Liczba równań:");
    Fl_Output *output = new Fl_Output(50, 100, 200, 30, "Output:");
    Fl_Output *output_it = new Fl_Output(50, 140, 200, 30, "Output it:");
    Fl_Button *btn_number_equations = new Fl_Button(50, 50, 100, 40, "Zapisz");
    Fl_Input *input_x = new Fl_Input(50, 200, 200, 30, "x[i]:");
    Fl_Input *inbut_xb = new Fl_Input(50, 220, 200, 30, "x[i].b:");
    Fl_Button *btn_x = new Fl_Button(50, 250, 100, 40, "Zapisz x[i]");
    Fl_Button *btn_calculate = new Fl_Button(50, 300, 100, 40, "Oblicz");
    Fl_Box *box_i = new Fl_Box(50, 350, 200, 30, "i = 0");
    Fl_Output *output_st = new Fl_Output(50, 400, 200, 30, "Output st:");
    Fl_Button *btn_reset = new Fl_Button(50, 400, 100, 40, "Reset");
    Fl_Widget* widgets[7] = {input_number_equations, output, output_it, input_x, inbut_xb, box_i, output_st};

    choice->callback(on_choice, widgets);
    choice->value(0); 
    inbut_xb->hide();
    btn_number_equations->callback(get_number_equations,widgets);
    btn_x->callback(save_x, widgets);
    btn_calculate->callback(calculate, widgets);
    btn_reset->callback(reset, widgets);




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