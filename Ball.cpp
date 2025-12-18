#include "Ball.h"
#include <FL/fl_draw.H> 
#include <FL/Fl_PNG_Image.H>
#include <ctime>

Ball::Ball(Point xy, int rr) : Circle(xy, rr), prevPos(xy) {
}

int Ball::get_dx() const {
    return dx;
}

int Ball::get_dy() const {
    return dy;
}

void Ball::set_dx(int v) {
    dx = v;
}

void Ball::set_dy(int v) {
    dy = v;
}

void Ball::move(int dx, int dy) {
    prevPos = point(0);
    Shape::move(dx, dy);
}

void Ball::triggerHappySmile() {
    happySmile = true;
    happySmileStartTime = std::time(nullptr);
}

void Ball::draw_lines() const {
    int x = center().x - radius();
    int y = center().y - radius();
    int size = radius() * 2;
    
    if (happySmile && std::time(nullptr) - happySmileStartTime > 0.6) {
        happySmile = false;
    }
    
    const char* texturePath = happySmile ? 
    "sources/textures/dovolny_smile.png" :
    "sources/textures/smile.png";
    
    Fl_PNG_Image texture(texturePath);
    
    if (texture.w() > 0) {
        texture.draw(x, y, size, size);
    } else {
        fl_color(FL_YELLOW);
        fl_pie(x, y, size, size, 0, 360);
    }
    
    fl_color(FL_BLACK);
    fl_arc(x, y, size, size, 0, 360);
}