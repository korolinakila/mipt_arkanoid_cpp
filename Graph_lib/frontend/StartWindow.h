#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "Graph_lib/Window.h"
#include "Graph_lib/GUI.h"


class StartWindow : public Graph_lib::Window {
public:
    StartWindow(Graph_lib::Point xy, int w, int h, const std::string& title);
    
    
private:
    Graph_lib::Button* button;
    
    
    static void button_callback(Graph_lib::Address, Graph_lib::Address pw);
    void button_pressed();
};

#endif 