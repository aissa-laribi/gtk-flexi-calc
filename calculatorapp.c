#include <gtk/gtk.h>

#include "calculatorapp.h"
#include "calculatorappwin.h"
#include "calculatorbutton.h"

struct _CalculatorApp{
    GtkApplication parent;
};

typedef struct _CalculatorApp CalculatorApp;

G_DEFINE_TYPE (CalculatorApp, calculator_app, GTK_TYPE_APPLICATION);

static void calculator_app_init(CalculatorApp *app){

}

static void  calculator_app_activate (GApplication *app){
    CalculatorAppWindow *win;

    win = calculator_app_window_new (CALCULATOR_APP (app));
    gtk_window_present (GTK_WINDOW (win));
}



static void calculator_app_class_init (CalculatorAppClass *class){
    G_APPLICATION_CLASS (class)->activate = calculator_app_activate;
}

CalculatorApp *calculator_app_new(void){
    return g_object_new (CALCULATOR_APP_TYPE,
                         "application-id", "org.gtk.calculatorapp",
                         "flags", G_APPLICATION_HANDLES_OPEN, NULL );    
}



