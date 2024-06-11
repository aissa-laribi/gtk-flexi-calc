#include <gtk/gtk.h>
#include "calculatorapp.h"
#include "calculatorappwin.h"

// Function to load CSS styles
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

int main(int argc, char **argv) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Load CSS styles
    load_css();

    // Create and run the application
    CalculatorApp *app = calculator_app_new();
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
