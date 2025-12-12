#include "ArkanoidWindow.h"
#include "Graph_lib/Window.h"

using namespace Graph_lib;


ArkanoidWindow::ArkanoidWindow(Point xy, int w, int h, const std::string &title) :
        Window{xy, w, h, title} {
    startScreen = new StartScreen{0, 0, w, h, *this};
    gameScreen = new GameScreen{0, 0, w, h};

    add(startScreen);
    add(gameScreen);
    init();

    startScreen->show();
    gameScreen->hide();
}

void ArkanoidWindow::openGameScreen() {
    gameScreen->show();
    startScreen->hide();

    Fl::add_timeout(0.016, [](void* userdata) -> void {
        GameScreen* screen = static_cast<GameScreen*>(userdata);
        screen->TimerCallback(userdata);
    }, gameScreen);
}
