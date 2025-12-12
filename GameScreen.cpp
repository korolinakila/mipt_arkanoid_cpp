#include "GameScreen.h"
#include "Fl/Fl.H"
#include "Fl/Fl_Group.H"


GameScreen::GameScreen(int x, int y, int w, int h) :
        Fl_Group(x, y, w, h),
        platform{Point{350, 750}, 100, 20},
        ball{Point{50, 100}, 10}{
    attach(platform);
    attach(ball);
}

int GameScreen::handle(int event) {
    if (event == FL_SHORTCUT && visible()) {
        switch (Fl::event_key()) {
            case FL_Left:
                platform.move(-30, 0);
                break;
            case FL_Right:
                platform.move(30, 0);
                break;
        }
        return 1;
    }
    return 0;
}

void GameScreen::draw() {
    Fl_Group::draw();
    fl_color(FL_GRAY);
    fl_rectf(x(), y(), w(), h());
    for (unsigned int i = 0; i < shapes.size(); ++i)
        shapes[i]->draw();
}

void GameScreen::TimerCallback(void* userdata) {
    int dx = ball.get_dx();
    int dy = ball.get_dy();
    ball.move(dx, dy);

    Point p = ball.point(0);
    int x = p.x;
    int y = p.y;
    int r = ball.radius();

    if (x + 2 * r > 800 || x < 0) {
        ball.set_dx(-dx);
    }
    if (y + 2 * r > 800 || y < 0) {
        ball.set_dy(-dy);
    }

    redraw();

    Fl::repeat_timeout(0.016, [](void* userdata) -> void {
        GameScreen* screen = static_cast<GameScreen*>(userdata);
        screen->TimerCallback(userdata);
    }, this);
}
