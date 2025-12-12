#ifndef ARKANOID_STARTSCREEN_H
#define ARKANOID_STARTSCREEN_H

#include "Fl/Fl_Group.H"
//#include "ArkanoidWindow.h"
#include "Graph_lib/Window.h"


class StartScreen : public Fl_Group {
public:
    StartScreen(int x, int y, int w, int h, Graph_lib::Window& window);
};


#endif //ARKANOID_STARTSCREEN_H
