#ifndef ARKANOID_BALL_H
#define ARKANOID_BALL_H

#include "Graph_lib/Graph.h"

using namespace Graph_lib;


class Ball : public Circle {
public:
    Ball(Point xy, int rr);

    int get_dx() const;
    int get_dy() const;

    void set_dx(int v);
    void set_dy(int v);

    void move (int dx, int dy) override;

    Point getPrevPos() const {return prevPos;}

private:
    Point prevPos;
    int dx = 2;
    int dy = 2;
};


#endif //ARKANOID_BALL_H
