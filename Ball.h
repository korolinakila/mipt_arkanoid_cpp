#ifndef ARKANOID_BALL_H
#define ARKANOID_BALL_H

#include "Graph_lib/Graph.h"
#include <ctime>

using namespace Graph_lib;


class Ball : public Circle {
public:
    Ball(Point xy, int rr);

    int get_dx() const;
    int get_dy() const;

    void set_dx(int v);
    void set_dy(int v);

    void move (int dx, int dy) override;
    void draw_lines() const override;

    Point getPrevPos() const {return prevPos;}

    void triggerHappySmile();

private:
    Point prevPos;
    int dx = 4;
    int dy = 4;
    mutable bool happySmile = false;
    mutable std::time_t happySmileStartTime = 0;
};


#endif //ARKANOID_BALL_H
