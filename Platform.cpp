#include "Platform.h"
#include "Graph_lib/Graph.h"
#include "iostream"

using namespace Graph_lib;


Platform::Platform(Point xy, int ww, int hh) : Rectangle(xy, ww, hh) {

}

void Platform::move(int dx, int dy) {
    Shape::move(dx, dy);

    int x = point(0).x;
    if (x < 0) {
        move(abs(x), 0);
    }
    if (x + width() > 800) { // 800 - window width
        move((800 - width() - x), 0);
    }
}