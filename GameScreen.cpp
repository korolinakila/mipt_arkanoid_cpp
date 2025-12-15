#include "GameScreen.h"
#include "Settings.h"
#include <cmath>

GameScreen::GameScreen(int x, int y, int w, int h) :
        Fl_Group(x, y, w, h),
        platform{Point{platformStartX, platformY}, platformWidth, platformHeight},
        ball{Point{50, 100}, ballRadius},
        blocks{10, 10} {
    attach(platform);
    attach(ball);

    for (int i = 0; i < blocks.getMatrixHeight(); i++) {
        for (int j = 0; j < blocks.getMatrixWidth(); j++) {
            Block* b = blocks.get_block(i, j);
            attach((Shape&) *b);
        }
    }
}

void GameScreen::detach(Graph_lib::Shape &s) {
    for (unsigned int i = shapes.size(); 0 < i; --i)  // guess last attached will be first released
        if (shapes[i - 1] == &s)
            shapes.erase(shapes.begin() + (i - 1));  // &shapes[i-1]);
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

    if (auto [i, j] = checkTopCollideBallWithBlocks(); i != -1 && j != -1) {
        detach((Shape&) *blocks.get_block(i, j));
        blocks.del_block(i, j);
        ball.set_dy(-dy);
    }

    if (auto [i, j] = checkBottomCollideBallWithBlocks(); i != -1 && j != -1) {
        detach((Shape&) *blocks.get_block(i, j));
        blocks.del_block(i, j);
        ball.set_dy(-dy);
    }

    if (auto [i, j] = checkLeftCollideBallWithBlocks(); i != -1 && j != -1) {
        detach((Shape&) *blocks.get_block(i, j));
        blocks.del_block(i, j);
        ball.set_dx(-dx);
    }

    if (auto [i, j] = checkRightCollideBallWithBlocks(); i != -1 && j != -1) {
        detach((Shape&) *blocks.get_block(i, j));
        blocks.del_block(i, j);
        ball.set_dx(-dx);
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

std::pair<int, int> GameScreen::checkTopCollideBallWithBlocks() {
    Point p1 = ball.point(0);
    int x1 = p1.x;
    int y1 = p1.y;
    int prev_y1 = ball.getPrevPos().y;

    int w = blocks.getBlockWidth();
    int h = blocks.getBlockHeight();

    for (int i = 0; i < blocks.getMatrixHeight(); i++) {
        for (int j = 0; j < blocks.getMatrixWidth(); j++) {
            Block* block = blocks.get_block(i, j);
            if (block == nullptr) {
                continue;
            }

            Point p2 = block->point(0);
            int x2 = p2.x;
            int y2 = p2.y;

            if ((y1 + 2 * ballRadius >= y2 && y1 <= y2 + h) &&
                (prev_y1 + 2 * ballRadius < y2) &&
                (x2 <= x1 + 2 * ballRadius && x1 <= x2 + w)) {
                return std::pair<int, int>(i, j);
            }
        }
    }

    return std::pair<int, int>(-1, -1);
}

std::pair<int, int> GameScreen::checkBottomCollideBallWithBlocks() {
    Point p1 = ball.point(0);
    int x1 = p1.x;
    int y1 = p1.y;
    int prev_y1 = ball.getPrevPos().y;

    int w = blocks.getBlockWidth();
    int h = blocks.getBlockHeight();

    for (int i = 0; i < blocks.getMatrixHeight(); i++) {
        for (int j = 0; j < blocks.getMatrixWidth(); j++) {
            Block* block = blocks.get_block(i, j);
            if (block == nullptr) {
                continue;
            }

            Point p2 = block->point(0);
            int x2 = p2.x;
            int y2 = p2.y;

            if ((y2 + h >= y1 && y2 <= y1 + 2 * ballRadius) &&
                !(y2 + h >= prev_y1 && y2 + h <= prev_y1 + 2 * ballRadius) &&
                (x2 <= x1 + 2 * ballRadius && x1 <= x2 + w)) {
                return std::pair<int, int>(i, j);
            }
        }
    }

    return std::pair<int, int>(-1, -1);
}

std::pair<int, int> GameScreen::checkLeftCollideBallWithBlocks() {
    Point p1 = ball.point(0);
    int x1 = p1.x;
    int y1 = p1.y;
    int prev_x1 = ball.getPrevPos().x;

    int w = blocks.getBlockWidth();
    int h = blocks.getBlockHeight();

    for (int i = 0; i < blocks.getMatrixHeight(); i++) {
        for (int j = 0; j < blocks.getMatrixWidth(); j++) {
            Block *block = blocks.get_block(i, j);
            if (block == nullptr) {
                continue;
            }

            Point p2 = block->point(0);
            int x2 = p2.x;
            int y2 = p2.y;

            if ((x1 + 2 * ballRadius >= x2 && x1 <= x2 + w) &&
                (prev_x1 + 2 * ballRadius < x2) &&
                (y2 <= y1 + 2 * ballRadius && y1 <= y2 + h)) {
                return std::pair<int, int>(i, j);
            }
        }
    }

    return std::pair<int, int>(-1, -1);
}

std::pair<int, int> GameScreen::checkRightCollideBallWithBlocks() {
    Point p1 = ball.point(0);
    int x1 = p1.x;
    int y1 = p1.y;
    int prev_x1 = ball.getPrevPos().x;

    int w = blocks.getBlockWidth();
    int h = blocks.getBlockHeight();

    for (int i = 0; i < blocks.getMatrixHeight(); i++) {
        for (int j = 0; j < blocks.getMatrixWidth(); j++) {
            Block *block = blocks.get_block(i, j);
            if (block == nullptr) {
                continue;
            }

            Point p2 = block->point(0);
            int x2 = p2.x;
            int y2 = p2.y;

            if ((x2 + w >= x1 && x2 <= x1 + 2 * ballRadius) &&
                !(x2 + w >= prev_x1 && x2 + w <= prev_x1 + 2 * ballRadius) &&
                (y2 <= y1 + 2 * ballRadius && y1 <= y2 + h)) {
                return std::pair<int, int>(i, j);
            }
        }
    }

    return std::pair<int, int>(-1, -1);
}