#include "ArkanoidWindow.h"
#include "Graph_lib/Graph.h"
#include "Graph_lib/Window.h"
#include <iostream>
#include "Graph_lib/GUI.h"
using namespace Graph_lib;

ArkanoidWindow::ArkanoidWindow(Point xy, int w, int h, const std::string &title) : Window{xy, w, h, title} {
    init();
}


int ArkanoidWindow::handle(int event) {
    if (event == FL_SHORTCUT) {
        switch (Fl::event_key()) {
            case FL_Left:
                rect->move(-30, 0);
                break;
            case FL_Right:
                rect->move(30, 0);
                break;
        }
        this->redraw();
        return 1;
    }
    return 0;
}
