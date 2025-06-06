#include "gui.h"
#include "functions.h"
#include <string>
#include <dlfcn.h>
int number_eq;
int index_x = 0;
int option = 0;
vector<mpreal> x_values_real;
vector<Interval<mpreal>> x_values_interval;

void reset(Fl_Widget* widget, void* data) 
{
    auto** widgets = static_cast<Fl_Widget**>(data);
    Fl_Input* input_number_equations = static_cast<Fl_Input*>(widgets[0]);
    Fl_Output* output = static_cast<Fl_Output*>(widgets[1]);
    Fl_Output* output_it = static_cast<Fl_Output*>(widgets[2]);
    Fl_Input* input_x = static_cast<Fl_Input*>(widgets[3]);
    Fl_Box* box_i = static_cast<Fl_Box*>(widgets[5]);

    input_number_equations->value("");
    output->value("");
    output_it->value("");
    input_x->value("");
    box_i->label("i = 0");
    
    number_eq = 0;
    index_x = 0;
    x_values_real.clear();
}

void calculate(Fl_Widget* widget, void* data) 
{
    void* handle = dlopen("./equations.so", RTLD_LAZY);
    F f =(F)dlsym(handle, "f");
    DF df =(DF)dlsym(handle, "df");
    FI fi =(FI)dlsym(handle, "fi");
    DFI dfi =(DFI)dlsym(handle, "dfi");
    auto** widgets = static_cast<Fl_Widget**>(data);
    Fl_Output* output = static_cast<Fl_Output*>(widgets[1]);
    Fl_Output* output_it =static_cast<Fl_Output*>(widgets[2]);
    Fl_Input* output_st = static_cast<Fl_Input*>(widgets[6]);
    int it = 0;
    int st = 0;
    if (option == 0)
    {
        NewtonSimpleNormal(
            number_eq, 
            x_values_real,
            f, 
            df, 
            mpreal(0.8), 
            mpreal(1e-16), 
            150, 
            it, 
            st
        );
    }
    else
    {
        NewtonSimpleInterval(
            number_eq, 
            x_values_interval, 
            fi, 
            dfi, 
            Interval<mpreal>(0.8, 0.8), 
            mpreal(1e-16), 
            150, 
            it, 
            st
        );
    }
    /*string xs = x_values_real[0].toString();
    const char* xc = xs.c_str();
    string its = to_string(it);
    const char* itc = its.c_str();
    output->value(xc); 
    output_it->value(itc);*/
    string sts = to_string(st);
    const char* stc = sts.c_str();
    output_st->value(stc);
    string its = to_string(it);
    const char* itc = its.c_str();
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
    auto** widgets = static_cast<Fl_Widget**>(data);
    Fl_Choice* choice = static_cast<Fl_Choice*>(widget);
    Fl_Input* input_x = static_cast<Fl_Input*>(widgets[3]);
    Fl_Input* inbut_xb = static_cast<Fl_Input*>(widgets[4]);
    option = choice->value();
    switch (option) {
        case 0:
            input_x->label("x[i]:");
            inbut_xb->hide();
            break;
        case 1:
            input_x->label("x[i]:");
            inbut_xb->hide();
            break;
        case 2:
            input_x->label("x[i].a:");
            inbut_xb->show();
            break;
        default:
            cout << "Nieznana opcja." << endl;
            break;
    }

}

void save_x(Fl_Widget* widget, void* data) 
{
    auto** widgets = static_cast<Fl_Widget**>(data);
    Fl_Input* input_x = static_cast<Fl_Input*>(widgets[3]);
    if (option == 0)
    {
        mpreal x_value = mpreal(input_x->value());
        if (index_x < number_eq) {
            x_values_real.push_back(x_value);
            index_x++;
            cout << "Zapisano x[" << index_x - 1 << "] = " << x_value << endl;
        } else {
            cout << "Przekroczono liczbę równań." << endl;
        }
        Fl_Box* box_i = static_cast<Fl_Box*>(widgets[5]);
        string index_str = "i = " + to_string(index_x);
        const char* index_cstr = index_str.c_str();
        box_i->label(index_cstr);
        input_x->value("");
    }
    else if (option == 1)
    {
        if (index_x < number_eq) {
            Interval<mpreal> temp;
            temp = IntRead<mpreal>(input_x->value());
            x_values_interval.push_back(temp);
            index_x++;
        } else {
            cout << "Przekroczono liczbę równań." << endl;
        }
        Fl_Box* box_i = static_cast<Fl_Box*>(widgets[5]);
        string index_str = "i = " + to_string(index_x);
        const char* index_cstr = index_str.c_str();
        box_i->label(index_cstr);
        input_x->value("");
        
    }
    else if (option == 2)
    {
        Fl_Input* inbut_xb = static_cast<Fl_Input*>(widgets[4]);
        if (index_x < number_eq) {
            Interval<mpreal> temp;
            temp.a = LeftRead<mpreal>(input_x->value());
            temp.b = RightRead<mpreal>(inbut_xb->value());
            x_values_interval.push_back(temp);
            index_x++;
        } else {
            cout << "Przekroczono liczbę równań." << endl;
        }
        Fl_Box* box_i = static_cast<Fl_Box*>(widgets[5]);
        string index_str = "i = " + to_string(index_x);
        const char* index_cstr = index_str.c_str();
        box_i->label(index_cstr);
        input_x->value("");
        inbut_xb->value("");
        
    }

}

