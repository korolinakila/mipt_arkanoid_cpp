#include "GameScreen.h"
#include <cmath>

GameScreen::GameScreen(int x, int y, int w, int h) :
        Fl_Group(x, y, w, h),
        platform{Point{350, 785}, 100, 10},
        ball{Point{50, 100}, 10}{
    attach(platform);
    attach(ball);
}

int GameScreen::handle(int event) {
    platform.setPos(std::min(std::max(Fl::event_x(), 0), w() - platform.width()), platform.point(0).y);
    return 0;
}

void GameScreen::draw() {
    Fl_Group::draw();
    fl_color(FL_GRAY);
    fl_rectf(x(), y(), w(), h());
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
        double w = platform.width() / 2;

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
    int r = ball.radius();

    Point p2 = platform.point(0);
    int x2 = p2.x;
    int y2 = p2.y;
    int w = platform.width();
    int h = platform.height();

    return ((y1 + 2 * r >= y2 && y1 + 2 * r <= y2 + h) && (prev_y1 + 2 * r < y2) && (x2 <= x1 + r && x1 + r <= x2 + w));
}

bool GameScreen::collideBallWithWalls() const {
    int x = ball.point(0).x;
    return (x + 2 * ball.radius() > 800 || x < 0);
}

bool GameScreen::collideBallWithRoof() const {
    return ball.point(0).y <= 0;
}

bool GameScreen::collideBallWithFloor() const {
    return ball.point(0).y + 2 * ball.radius() >= 800;
}
