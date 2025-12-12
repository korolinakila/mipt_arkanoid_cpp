#ifndef ARKANOID_ARKANOIDWINDOW_H
#define ARKANOID_ARKANOIDWINDOW_H

#include "Graph_lib/Window.h"
#include "Graph_lib/Graph.h"
#include "Platform.h"
#include "StartScreen.h"
#include "GameScreen.h"

using namespace Graph_lib;


class ArkanoidWindow : public Graph_lib::Window {
public:
    ArkanoidWindow(Point xy, int w, int h, const std::string& title);

    virtual ~ArkanoidWindow() = default;

    void openGameScreen();

private:
    StartScreen* startScreen;
    GameScreen* gameScreen;

};

#endif //ARKANOID_ARKANOIDWINDOW_H
