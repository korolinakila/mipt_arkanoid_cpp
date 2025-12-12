#include "GameScreen.h"
#include "Fl/Fl.H"
#include "Fl/Fl_Group.H"


GameScreen::GameScreen(int x, int y, int w, int h) :
        Fl_Group(x, y, w, h),
        platform{Point{350, 750}, 100, 20} {
    attach(platform);
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
        this->redraw();
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