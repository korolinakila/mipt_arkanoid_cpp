#include <FL/Fl.H>
#include "Graph_lib/Graph.h"
#include "Graph_lib/Window.h"
#include "ArkanoidWindow.h"
#include <iostream>

using namespace Graph_lib;


int main() {

    ArkanoidWindow window{Point{500, 200}, 800, 800, "arkanoid"};
    Rectangle rect{Point{350, 500}, 100, 20};

    window.rect = &rect;
    window.attach(rect);

    return Fl::run();

}

