#ifndef ARKANOID_GAMESCREEN_H
#define ARKANOID_GAMESCREEN_H

#include "FL/Fl_Group.H"
#include "Platform.h"


class GameScreen : public Fl_Group {
public:
    GameScreen(int x, int y, int w, int h);

    void attach(Shape& s) { shapes.push_back(&s); }

protected:
    void draw() override;


private:
    std::vector<Shape*> shapes;

    Platform platform;
    int handle(int event) override;

};


#endif //ARKANOID_GAMESCREEN_H
