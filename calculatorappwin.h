#ifndef __CALCULATORAPPWIN_H
#define __CALCULATORAPPWIN_H

#include <gtk/gtk.h>
#include "calculatorapp.h"



#define CALCULATOR_APP_WINDOW_TYPE (calculator_app_window_get_type ())
G_DECLARE_FINAL_TYPE (CalculatorAppWindow, calculator_app_window, CALCULATOR, APP_WINDOW, GtkApplicationWindow)


CalculatorAppWindow *calculator_app_window_new (CalculatorApp *app);
#endif 
