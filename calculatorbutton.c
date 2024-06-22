#include <gtk/gtk.h>

#include "calculatorapp.h"
#include "calculatorappwin.h"
#include "calculatorbutton.h"

struct _CalculatorButton{
    GtkButton parent;
    int negative;
    int digit;
    // Define other members as needed
};

G_DEFINE_TYPE(CalculatorButton, calculator_button, GTK_TYPE_BUTTON);

void calculator_button_init(){

}

static void calculator_button_class_init(CalculatorButtonClass *class){

}