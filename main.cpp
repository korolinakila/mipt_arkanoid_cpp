#include "Graph_lib/Graph.h"
#include "ArkanoidWindow.h"
#include <FL/Fl.H>
#include "Settings.h"

using namespace Graph_lib;


int main() {
    ArkanoidWindow window{Point{500, 200}, windowWidth, windowHeight, "arkanoid"};

    return Fl::run();
}