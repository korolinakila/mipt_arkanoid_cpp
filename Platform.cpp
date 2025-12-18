#include "Platform.h"
#include "Graph_lib/Graph.h"
#include "iostream"
#include <FL/fl_draw.H>
#include <FL/Fl_PNG_Image.H>
#include <ctime>
using namespace Graph_lib;


Platform::Platform(Point xy, int ww, int hh) : Rectangle(xy, ww, hh) {

}

void Platform::setPos(int x, int y) {
    set_point(0, Point{x, y});
}

void Platform::triggerAwake() {
    awake = true;
    awakeStartTime = std::time(nullptr);
}

void Platform::draw_lines() const {
    int x = point(0).x;
    int y = point(0).y;
    int w = width();
    int h = height();
    

    if (awake && std::time(nullptr) - awakeStartTime > 0.4) {
        awake = false;
    }
    

    const char* texturePath = awake ? 
        "sources/textures/awaked_platform.png" :
        "sources/textures/sleepy_platform.png";
    
    Fl_PNG_Image texture(texturePath);
    
    if (texture.w() > 0) {
        texture.draw(x, y, w, h);
    } else {
        fl_color(awake ? FL_RED : FL_BLUE);
        fl_rectf(x, y, w, h);
    }
    
    fl_color(FL_BLACK);
    fl_rect(x, y, w, h);
}