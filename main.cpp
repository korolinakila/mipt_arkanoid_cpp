#include <FL/Fl.H>
#include "Graph_lib/Window.h"
#include "ArkanoidWindow.h"
#include "backend/Platform.h"
#include "frontend/PlatformShape.h"
#include "frontend/StartWindow.h" 
#include <iostream>

using namespace Graph_lib;


int main() {
    extern bool clicked;
    StartWindow win(Point(100, 100), 400, 300, "Стартовое окно");
    win.show();
    Fl::run();

    if (clicked==true){
    ArkanoidWindow window{Point{500, 200}, 800, 800, "arkanoid"};
    Platform platform{350, 500, 100, 20};
    PlatformShape platformShape{platform};

    window.platform = &platformShape;
    window.attach(platformShape);

    return Fl::run();}

return -1;

}

