#include "GameScreen.h"
#include "Settings.h"
#include <cmath>

GameScreen::GameScreen(int x, int y, int w, int h) :
        Fl_Group(x, y, w, h),
        platform{Point{platformStartX, platformY}, platformWidth, platformHeight},
        ball{Point{50, 100}, ballRadius},
        blocks{20, 20} {
    attach(platform);
    attach(ball);

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            Block* b = blocks.get_block(i, j);
            attach((Shape&) *b);
        }
    }
}

int GameScreen::handle(int event) {
    platform.setPos(std::min(std::max(Fl::event_x() - platformWidth / 2, 0), windowWidth - platformWidth), platformY);
    return 0;
}

void GameScreen::draw() {
    Fl_Group::draw();
    fl_color(FL_GRAY);
    fl_rectf(x(), y(), windowWidth, windowHeight);
    for (unsigned int i = 0; i < shapes.size(); ++i)
        shapes[i]->draw();
}

void GameScreen::updateFrame(void *userdata) {
    int dx = ball.get_dx();
    int dy = ball.get_dy();
    ball.move(dx, dy);

    if (collideBallWithWalls()) {
        ball.set_dx(-dx);
    }
    if (collideBallWithRoof()) {
        ball.set_dy(-dy);
    }

    if (collideBallWithPlatform()) {
        Point collidePoint = ball.center();
        int x = collidePoint.x;
        double w = platformWidth / 2;

        int new_dx = std::round((x - platform.point(0).x - w) / w * abs(dy));

        ball.set_dx(new_dx);
        ball.set_dy(-std::round(std::sqrt(dx * dx + dy * dy - new_dx * new_dx)));

    }
    if (collideBallWithFloor()) {
        ball.set_dy(0); // TODO: game over screen
        ball.set_dx(0);
    }

    redraw();

    Fl::repeat_timeout(0.016, [](void* userdata) -> void {
        GameScreen* screen = static_cast<GameScreen*>(userdata);
        screen->updateFrame(userdata);
    }, this);
}


bool GameScreen::collideBallWithPlatform() const {
    Point p1 = ball.point(0);
    int x1 = p1.x;
    int y1 = p1.y;
    int prev_y1 = ball.getPrevPos().y;

    Point p2 = platform.point(0);
    int x2 = p2.x;

    return
            (y1 + 2 * ballRadius >= platformY && y1 + 2 * ballRadius <= platformY + platformHeight) &&
            (prev_y1 + 2 * ballRadius < platformY) &&
            (x2 <= x1 + 2 * ballRadius && x1 <= x2 + platformWidth);
}

bool GameScreen::collideBallWithWalls() const {
    int x = ball.point(0).x;
    return (x + 2 * ball.radius() > windowWidth || x < 0);
}

bool GameScreen::collideBallWithRoof() const {
    return ball.point(0).y <= 0;
}

bool GameScreen::collideBallWithFloor() const {
    return ball.point(0).y + 2 * ball.radius() >= windowHeight;
}
