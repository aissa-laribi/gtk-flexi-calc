#ifndef __CALCULATORAPP_H
#define __CALCULATORAPP_H

#include <gtk/gtk.h>

#define CALCULATOR_APP_TYPE (calculator_app_get_type() )

G_DECLARE_FINAL_TYPE (CalculatorApp, calculator_app, CALCULATOR, APP, GtkApplication)

struct _CalculatorButton {
    GtkButton parent;
    int negative;
    int digit;
    // Define other members as needed
};

CalculatorApp *calculator_app_new(void);


#endif