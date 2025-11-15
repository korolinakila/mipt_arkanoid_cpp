#ifndef ARKANOID_ARKANOIDWINDOW_H
#define ARKANOID_ARKANOIDWINDOW_H

#include "Graph_lib/Window.h"
#include "Graph_lib/Graph.h"

using namespace Graph_lib;

class ArkanoidWindow : public Graph_lib::Window {
public:
    ArkanoidWindow(Point xy, int w, int h, const std::string& title);

    virtual ~ArkanoidWindow() = default;

    Rectangle* rect = nullptr;
private:
    int handle(int event) override;
};

#endif //ARKANOID_ARKANOIDWINDOW_H
