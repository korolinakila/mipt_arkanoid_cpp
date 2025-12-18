#ifndef ARKANOID_PLATFORM_H
#define ARKANOID_PLATFORM_H

#include "Graph_lib/Graph.h"
#include <ctime>

using namespace Graph_lib;

class Platform : public Rectangle {
public:
    Platform(Point xy, int ww, int hh);
    void draw_lines() const override;
    void setPos(int x, int y);
    void triggerAwake();
    
private:
    mutable bool awake = false;
    mutable std::time_t awakeStartTime = 0;
};

#endif //ARKANOID_PLATFORM_H