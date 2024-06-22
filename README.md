# GTK Flexi Calc

Scalable calculator with basic arithmetic operations (addition, subtraction, and multiplication) built with the GTK Framework

Currently in development

## Usage

`glib-compile-resources calculatorapp.gresource.xml --target=resources.c --generate-source`

gcc -o calculatorapp main.c calculatorapp.c calculatorappwin.c resources.c calculatorbutton.c `pkg-config --cflags --libs gtk+-3.0` -rdynamic
