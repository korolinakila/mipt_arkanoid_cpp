#include <FL/Fl.H>
#include "Graph_lib/Graph.h"
#include "ArkanoidWindow.h"

using namespace Graph_lib;


int main() {
    ArkanoidWindow window{Point{500, 200}, 800, 800, "arkanoid"};

    return Fl::run();

}

