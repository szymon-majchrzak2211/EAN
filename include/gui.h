#ifndef GUI_H
#define GUI_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Box.H>
#include "functions.h"
#include <iostream>

void calculate(Fl_Widget* widget, void*); 
void get_number_equations(Fl_Widget* widget, void* data);
void on_choice(Fl_Widget* widget, void* data);
void save_x(Fl_Widget* widget, void* data);
void reset(Fl_Widget* widget, void* data);

#endif


