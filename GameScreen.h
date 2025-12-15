#ifndef ARKANOID_GAMESCREEN_H
#define ARKANOID_GAMESCREEN_H

#include "FL/Fl_Group.H"
#include "Platform.h"
#include "Ball.h"
#include "BlocksMatrix.h"

class GameScreen : public Fl_Group {
public:
    GameScreen(int x, int y, int w, int h);

    void attach(Shape& s) { shapes.push_back(&s); }
    void detach(Shape& s);

    void updateFrame(void* userdata);

protected:
    void draw() override;


private:
    std::vector<Shape*> shapes;

    Platform platform;
    Ball ball;
    BlocksMatrix blocks;

    int handle(int event) override;

    bool collideBallWithPlatform() const;
    bool collideBallWithWalls() const;
    bool collideBallWithRoof() const;
    bool collideBallWithFloor() const;

    std::pair<int, int> checkTopCollideBallWithBlocks();
    std::pair<int, int> checkBottomCollideBallWithBlocks();
    std::pair<int, int> checkLeftCollideBallWithBlocks();
    std::pair<int, int> checkRightCollideBallWithBlocks();
};


#endif //ARKANOID_GAMESCREEN_H
