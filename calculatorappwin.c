#include <gtk/gtk.h>
#include <math.h>
#include "calculatorapp.h"
#include "calculatorappwin.h"
#include "calculatorbutton.h"



struct _CalculatorAppWindow {
    GtkApplicationWindow parent;
    GtkWidget *text_view; // Hold a reference to the text view
    GtkWidget *text_view_2;
    GtkTextBuffer *text_buffer; // Text buffer to update the text view
    GtkTextBuffer *text_buffer_2;
    gboolean zero;
    gboolean floating;
    gboolean addition;
    gboolean substraction;
    gboolean multiplication;
    gboolean division;
    gboolean ongoing_operand;
    gboolean modulo;
    gint exp_10;
    gint total;
    gint current_int_operand;
    gint previous_operand;
    gdouble current_float_operand;
    gdouble previous_float_operand;
    gdouble total_float;
    gint previous_operator; /*Mult: 1; Add: 2; Sub: 3; Div*/ 
};

G_DEFINE_TYPE(CalculatorAppWindow, calculator_app_window, GTK_TYPE_APPLICATION_WINDOW);

void total_display(CalculatorAppWindow *win) {
    gchar *total_label;
    GtkTextIter end_iter;
    if(!win->floating){
        total_label = g_strdup_printf("%d", win->total);
        //g_print("total string:%s:\n", total_label);

        gtk_text_buffer_set_text(win->text_buffer_2, "", -1);

        gtk_text_buffer_get_end_iter(win->text_buffer_2, &end_iter);

        gtk_text_buffer_insert(win->text_buffer_2, &end_iter, total_label, -1);

    
        //g_print("Current iteration: %s\n", total_label);
    } else if(win->floating){
        total_label = g_strdup_printf("%f", win->total_float);
        //g_print("total_float string:%s:\n", total_label);

        gtk_text_buffer_set_text(win->text_buffer_2, "", -1);

        gtk_text_buffer_get_end_iter(win->text_buffer_2, &end_iter);

        gtk_text_buffer_insert(win->text_buffer_2, &end_iter, total_label, -1);

    
        //g_print("Current iteration: %s\n", total_label);
    }
}

static void operation(CalculatorButton *button, CalculatorAppWindow *win){
    const gchar *button_label = gtk_button_get_label(GTK_BUTTON (button) );
    const gchar *button_label_ascii = g_str_to_ascii(button_label, button_label_ascii);
    int current;
    if(!win->floating){
        g_print("Not currently floating\n");
        g_print("Current Operand: %d Previous operand: %d\n", win->current_int_operand, win->previous_operand);
    } else if (win->floating){
        g_print("Currently floating\n");
        g_print("Current Float Operand: %f Previous Float operand: %f\n", win->current_float_operand, win->previous_float_operand);
    }
    current = (int) *button_label_ascii - 48;
    switch(current){
        case 72: /*Multiplication sign in ASCII*/
            if(!win->previous_operator){
                win->total += win->current_int_operand;
                win->previous_operand = win->current_int_operand;
                total_display(win);
                win->current_int_operand = 0;
                win->previous_operator = 1;
            } else if(win->previous_operator == 1){
                win->total *= win->current_int_operand;
                win->previous_operand = win->current_int_operand;
                total_display(win);
                win->current_int_operand = 0;
                win->previous_operator = 1;
            } else if(win->previous_operator == 2){
                //win->total -= win->previous_operand;
                //total_display(win);
                win->previous_operand = win->current_int_operand;
                win->current_int_operand = 0;
                win->previous_operator = 1;
            } else if(win->previous_operator == 3){
                win->current_int_operand *= (-1);
                win->previous_operand = win->current_int_operand;
                total_display(win);
                win->current_int_operand = 0;
                win->previous_operator = 1;
            } 
            win->addition = FALSE;
            win->substraction = FALSE;
            win->multiplication = TRUE;
            win->division = FALSE;
            win->modulo = FALSE;
            break;            
        case -5: /*Addition sign in ASCCI - 48*/
            
            if(!win->previous_operator){
                if(!win->floating){
                    win->total += win->current_int_operand;
                    win->previous_operand = win->current_int_operand;
                    total_display(win);
                    win->current_int_operand = 0;
                    win->previous_operator = 2;
                } else if(win->floating){
                    win->total_float += win->current_float_operand;
                    win->previous_float_operand = win->current_float_operand;
                    total_display(win);
                    win->current_float_operand = 0;
                    win->previous_operator = 2;
                }
                
            } else if(win->previous_operator == 1){
                if(!win->floating){
                    g_print("Win->total: %d, cur: %d, prev: %d", win->total,win->current_int_operand,win->previous_operand);
                    win->total += (win->current_int_operand * win->previous_operand);
                    win->previous_operand = win->current_int_operand;
                    total_display(win);
                    win->current_int_operand = 0;
                    win->previous_operator = 2;
                } else if(win->floating){
                    g_print("Win->total_float: %f, cur_float: %f, prev_float: %f", win->total_float,win->current_float_operand,win->previous_float_operand);
                    win->total_float += (win->current_float_operand * win->previous_float_operand);
                    win->previous_float_operand = win->current_float_operand;
                    total_display(win);
                    win->current_float_operand = 0;
                    win->previous_operator = 2;
                }

            } else if(win->previous_operator == 2){
                if (!win->floating){
                    win->total += win->current_int_operand ;
                    total_display(win);
                    win->previous_operand = win->current_int_operand;
                    win->current_int_operand = 0;
                    win->previous_operator = 2;
                } else if(win->floating) {
                    win->total_float += win->current_float_operand ;
                    total_display(win);
                    win->previous_float_operand = win->current_float_operand;
                    win->current_float_operand = 0.00;
                    win->previous_operator = 2;
                } 
            } else if(win->previous_operator == 3){
                if (!win->floating){
                    win->total -= win->current_int_operand;
                    total_display(win);
                    win->previous_operand = win->current_int_operand;
                    win->current_int_operand = 0;
                    win->previous_operator = 2;
                } else if (win->floating){
                    win->total_float -= win->current_float_operand;
                    total_display(win);
                    win->previous_float_operand = win->current_float_operand;
                    win->current_float_operand = 0;
                    win->previous_operator = 2;
                }
            } else if(win->previous_operator == 4){
                g_print("Win->total_float: %f, cur: %f, prev: %f", win->total_float,win->current_float_operand,win->previous_float_operand);                
                win->total_float /= win->current_float_operand;
                win->previous_float_operand = win->current_float_operand;
                total_display(win);
                win->current_float_operand = 0.00;
                win->previous_operator = 2;
            }
            win->addition = TRUE;
            win->substraction = FALSE;
            win->multiplication = FALSE;
            win->division = FALSE;
            win->modulo = FALSE;
            break;
        case -3: /*Substraction sign in ASCII*/
            if(!win->previous_operator){
                win->total -= win->current_int_operand;
                total_display(win);
                win->current_int_operand = 0;
                win->previous_operator = 3;
            } else if(win->previous_operator == 1){
                g_print("Win->total: %d, cur: %d, prev: %d", win->total,win->current_int_operand,win->previous_operand);
                win->total += (win->current_int_operand * win->previous_operand);
                win->previous_operand = win->current_int_operand;
                total_display(win);
                win->current_int_operand = 0;
                win->previous_operator = 3;
            } else if(win->previous_operator == 2){
                win->total += win->current_int_operand;
                total_display(win);
                win->current_int_operand = 0;
                win->previous_operator = 3;
            } else if(win->previous_operator == 3){
                win->total -= win->current_int_operand;
                total_display(win);
                win->current_int_operand = 0;
                win->previous_operator = 3;
            }
            win->addition = FALSE;
            win->substraction = TRUE;
            win->multiplication = FALSE;
            win->division = FALSE;
            win->modulo = FALSE;
            win->ongoing_operand = TRUE;
            break;
        case -1: /*Division sign in ASCCI - 48*/
            //if(!win->floating)
            //    win->total_float = (gdouble) win->total;
            if(!win->previous_operator){
                win->total += win->current_int_operand;
                win->total_float = (gdouble) win->total;
                win->previous_float_operand = win->total_float;
                total_display(win);
                win->current_float_operand = 0.00;
                win->previous_operator = 4;
            } else if(win->previous_operator == 1){
                if(!win->floating){ 
                    win->total *= win->current_int_operand;
                    win->previous_operand = win->current_int_operand;
                    total_display(win);
                    win->current_int_operand = 0;
                    win->previous_operator = 4;
                } else if(win->floating){
                    win->total_float *= win->current_float_operand;
                    win->previous_float_operand = win->current_float_operand;
                    total_display(win);
                    win->current_float_operand = 0.00;
                    win->previous_operator = 4;
                }
                } else if(win->previous_operator == 4){
                win->previous_float_operand = win->total_float;
                win->total_float /= win->current_float_operand;
                total_display(win);
                win->current_float_operand = 0.0;
                win->previous_operator = 4;
            }            
            win->addition = FALSE;
            win->substraction = FALSE;
            win->multiplication = FALSE;
            win->division = TRUE;
            win->modulo = FALSE;
            win->floating = TRUE;
            break;        
        case 0:
            if(win->zero){
                break;
            } else if (!win->floating) {
                win->current_int_operand *= 10;
                
                win->exp_10++;
                win->zero = FALSE;
                break;
            } else if (win->floating) {
                win->current_float_operand *= 10;
                
                win->exp_10++;
                win->zero = FALSE;
                break;
            } 
        case 1:
            if(!win->current_int_operand){
                win->current_int_operand += 1;

                win->exp_10++;
                win->zero = FALSE;
                break;
            } else if (!win->floating) {
                win->current_int_operand *= 10;
                win->current_int_operand += (1 % 10);

                break;
            } else if (win->floating) {
                win->current_float_operand *= 10;
                win->current_float_operand += (1 % 10);
                break;
            }
        case 2:
            if(!win->current_int_operand){
                win->current_int_operand += 2;

                win->exp_10++;
                win->zero = FALSE;
                break;
            } else if (!win->floating){
                win->current_int_operand *= 10;
                win->current_int_operand += (2 % 10);
                break;
            } else if (win->floating) {
                win->current_float_operand *= 10;
                win->current_float_operand += (2 % 10);
                break;
            }
        case 3:
            if(!win->current_int_operand){
                win->current_int_operand += 3;

                win->exp_10++;
                win->zero = FALSE;
                break;
            } else if (!win->floating){
                win->current_int_operand *= 10;
                win->current_int_operand += (3 % 10);
                break;
            } else if (win->floating) {
                win->current_float_operand *= 10;
                win->current_float_operand += (3 % 10);
                break;
            }
        case 4:
            if(!win->current_int_operand){
                win->current_int_operand += 4;

                win->exp_10++;
                win->zero = FALSE;
                break;
            } else if (!win->floating){
                win->current_int_operand *= 10;
                win->current_int_operand += (4 % 10);
                break;
            } else if (win->floating) {
                win->current_float_operand *= 10;
                win->current_float_operand += (4 % 10);
                break;
            }
        case 5:
            if(!win->current_int_operand){
                win->current_int_operand += 5;

                win->exp_10++;
                win->zero = FALSE;
                break;
            } else if (!win->floating){
                win->current_int_operand *= 10;
                win->current_int_operand += (5 % 10);
                break;
            } else if (win->floating) {
                win->current_float_operand *= 10;
                win->current_float_operand += (5 % 10);
                break;
            }
        case 6:
            if(!win->current_int_operand){
                win->current_int_operand += 6;
                win->exp_10++;
                win->zero = FALSE;
                break;
            } else if (!win->floating){
                win->current_int_operand *= 10;
                win->current_int_operand += (6 % 10);
                break;
            } else if (win->floating) {
                win->current_float_operand *= 10;
                win->current_float_operand += (6 % 10);
                break;
            }
        case 7:
            if(!win->current_int_operand){
                win->current_int_operand += 7;
                win->exp_10++;
                win->zero = FALSE;
                break;
            } else if (!win->floating){
                win->current_int_operand *= 10;
                win->current_int_operand += (7 % 10);
                break;
            } else if (win->floating) {
                win->current_float_operand *= 10;
                win->current_float_operand += (7 % 10);
                break;
            }
        case 8:
            if(!win->current_int_operand){
                win->current_int_operand += 8;
                win->exp_10++;
                win->zero = FALSE;
                break;
            } else if (!win->floating){
                win->current_int_operand *= 10;
                win->current_int_operand += (8 % 10);
                break;
            } else if (win->floating) {
                win->current_float_operand *= 10;
                win->current_float_operand += (8 % 10);
                break;
            }
        case 9:
            if(!win->current_int_operand){
                win->current_int_operand += 9;
                win->exp_10++;
                win->zero = FALSE;
                break;
            } else if (!win->floating){
                win->current_int_operand *= 10;
                win->current_int_operand += (9 % 10);
                break;
            } else if (win->floating) {
                win->current_float_operand *= 10;
                win->current_float_operand += (9 % 10);
                break;
            }
    }
}


static void on_button_clicked(CalculatorButton *button, CalculatorAppWindow *win) {
    const gchar *button_label = gtk_button_get_label(GTK_BUTTON (button) );
    const gchar *button_label_ascii = g_str_to_ascii(button_label, button_label_ascii);
    CalculatorButton *calc_button = CALCULATOR_BUTTON(button);

    
    GtkTextIter start_iter;    
    GtkTextIter end_iter; /*An iterator for the contents of a GtkTextBuffer*/
    //g_print("Current iteration: %d\n", (int) *button_label_ascii - 48);
    
    
    // Insert the button label into the text buffer
    gtk_text_buffer_get_end_iter(win->text_buffer, &end_iter);
    gtk_text_buffer_insert(win->text_buffer, &end_iter, button_label_ascii, -1);


    // Retrieve the iterators again after modifying the buffer
    gtk_text_buffer_get_start_iter(win->text_buffer, &start_iter);
    gtk_text_buffer_get_end_iter(win->text_buffer, &end_iter);

    //g_print("Buffer in Ascii: %s", gtk_text_buffer_get_text(win->text_buffer, &start_iter, &end_iter, FALSE));
    //g_print("Current ASCII value: %d\n", (int) *button_label_ascii - 48);
    operation(button, win);
    if(!win->floating){
        g_print("Total= %d\n", win->total);
    } else {
        g_print("Total float= %lf\n", win->total_float);
    }

}



static void calculator_app_window_class_init(CalculatorAppWindowClass *class) {
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(class), "/org/gtk/calculatorapp/window.ui");
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), CalculatorAppWindow, text_view); // Bind the text view
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), CalculatorAppWindow, text_view_2);
    gtk_widget_class_bind_template_callback(GTK_WIDGET_CLASS(class), on_button_clicked);
}

static void calculator_app_window_init(CalculatorAppWindow *win) {
    gtk_widget_init_template(GTK_WIDGET(win));
    win->text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(win->text_view));
    win->text_buffer_2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(win->text_view_2));
    win->zero = TRUE;
    win->exp_10 = 0;
    win->total = 0;
    win->current_int_operand = 0;
    win->total_float = 0.000000000000;
    win->floating = FALSE;
    win->addition = FALSE;
    win->substraction = FALSE;
    win->multiplication = FALSE;
    win->division = FALSE;
    win->modulo = FALSE;
    win->current_float_operand = 0.00;
}

CalculatorAppWindow *calculator_app_window_new(CalculatorApp *app) {
    return g_object_new(CALCULATOR_APP_WINDOW_TYPE, "application", app, NULL);
}

static void load_css(void) {
    GtkCssProvider *provider = gtk_css_provider_new();
    GError *error = NULL;

    if (!gtk_css_provider_load_from_path(provider, "style.css", &error)) {
        g_printerr("Error loading CSS file: %s\n", error->message);
        g_error_free(error);
    } else {
        GdkScreen *screen = gdk_screen_get_default();
        gtk_style_context_add_provider_for_screen(screen,
                                                  GTK_STYLE_PROVIDER(provider),
                                                  GTK_STYLE_PROVIDER_PRIORITY_USER);
        g_print("CSS loaded successfully.\n");
    }

    g_object_unref(provider);
}
