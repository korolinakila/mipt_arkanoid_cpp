#include "StartWindow.h"
#include <FL/Fl.H>
#include <iostream>

using namespace Graph_lib;
bool clicked = false;
StartWindow::StartWindow(Point xy, int w, int h, const std::string& title)
    : Window(xy, w, h, title)
{

    button = new Button(Point(w/2 - 50, h/2 - 25), 100, 50, "СТАРТ", button_callback);
    attach(*button);
    color(FL_WHITE);
}

void StartWindow::button_callback(Address, Address pw) {
    StartWindow& win = reference_to<StartWindow>(pw);
    win.button_pressed();
}

void StartWindow::button_pressed() {
    clicked = true;
    Fl::first_window()->hide(); 
}