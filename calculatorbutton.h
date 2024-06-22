#ifndef __CALCULATORBUTTON_H
#define __CALCULATORBUTTON_H

#include <gtk/gtk.h>
#include "calculatorapp.h"

#define CALCULATORBUTTON_TYPE (calculator_button_get_type ())
G_DECLARE_FINAL_TYPE (CalculatorButton, calculator_button, CALCULATOR, BUTTON, GtkButton)
#endif 