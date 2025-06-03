#include "gui.h"
#include "functions.h"
#include <string>
#include <dlfcn.h>
int number_eq;
int index_x = 0;
vector<mpreal> x_values_real;

void calculate(Fl_Widget* widget, void* data) 
{
    void* handle = dlopen("./equations.so", RTLD_LAZY);
    F f =(F)dlsym(handle, "f");
    DF df =(DF)dlsym(handle, "df");
    auto** widgets = static_cast<Fl_Widget**>(data);
    Fl_Output* output = static_cast<Fl_Output*>(widgets[1]);
    Fl_Output* output_it =static_cast<Fl_Output*>(widgets[2]);
    int it = 0;
    int st = 0;
    NewtonSimpleNormal(
        3, 
        x_values_real,
        f, 
        df, 
        mpreal(0.8), 
        mpreal(1e-16), 
        150, 
        it, 
        st
    );
    string xs = x_values_real[0].toString();
    const char* xc = xs.c_str();
    string its = to_string(it);
    const char* itc = its.c_str();
    output->value(xc); 
    output_it->value(itc);
}

void get_number_equations(Fl_Widget* widget, void* data) 
{
    auto** widgets = static_cast<Fl_Widget**>(data);
    Fl_Input* input = static_cast<Fl_Input*>(widgets[0]);
    number_eq = atoi(input->value());
    if (number_eq < 1) {
        cout << "Liczba równań musi być większa niż 0." << endl;
        return;
    }
    Fl_Output* output =   static_cast<Fl_Output*>(widgets[1]);
    string number_eqs = to_string(number_eq);
    const char* number_eqc = number_eqs.c_str();
    output->value(number_eqc);
}

void on_choice(Fl_Widget* widget, void* data) 
{
    Fl_Choice* choice = static_cast<Fl_Choice*>(widget);
    int value = choice->value();
    switch (value) {
        case 0:
            cout << "Rzeczywiste" << endl;
            break;
        case 1:
            cout << "Przedziałowe punktowe" << endl;
            break;
        case 2:
            cout << "Przedziałowe" << endl;
            break;
        default:
            cout << "Unknown choice" << endl;
    }
}

void save_x(Fl_Widget* widget, void* data) 
{
    auto** widgets = static_cast<Fl_Widget**>(data);
    Fl_Input* input_x = static_cast<Fl_Input*>(widgets[3]);
    mpreal x_value = mpreal(input_x->value());
    if (index_x < number_eq) {
        x_values_real.push_back(x_value);
        index_x++;
        cout << "Zapisano x[" << index_x - 1 << "] = " << x_value << endl;
    } else {
        cout << "Przekroczono liczbę równań." << endl;
    }
    Fl_Box* box_i = static_cast<Fl_Box*>(widgets[4]);
    string index_str = "i = " + to_string(index_x);
    const char* index_cstr = index_str.c_str();
    box_i->label(index_cstr);
    input_x->value("");
}

void reset(Fl_Widget* widget, void* data) 
{
    auto** widgets = static_cast<Fl_Widget**>(data);
    Fl_Input* input_number_equations = static_cast<Fl_Input*>(widgets[0]);
    Fl_Output* output = static_cast<Fl_Output*>(widgets[1]);
    Fl_Output* output_it = static_cast<Fl_Output*>(widgets[2]);
    Fl_Input* input_x = static_cast<Fl_Input*>(widgets[3]);
    Fl_Box* box_i = static_cast<Fl_Box*>(widgets[4]);

    input_number_equations->value("");
    output->value("");
    output_it->value("");
    input_x->value("");
    box_i->label("i = 0");
    
    number_eq = 0;
    index_x = 0;
    x_values_real.clear();
}