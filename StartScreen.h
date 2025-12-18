#ifndef ARKANOID_STARTSCREEN_H
#define ARKANOID_STARTSCREEN_H

#include <FL/Fl_Group.H>
#include <FL/Fl_PNG_Image.H>  
#include "Graph_lib/Window.h"

class StartScreen : public Fl_Group {
private:
    Fl_PNG_Image background;  
    
public:
    StartScreen(int x, int y, int w, int h, Graph_lib::Window& window);
    void draw() override;
};

#endif //ARKANOID_STARTSCREEN_H