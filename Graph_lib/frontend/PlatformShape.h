#ifndef ARKANOID_PLATFORMSHAPE_H
#define ARKANOID_PLATFORMSHAPE_H

#include "../backend/Platform.h"
#include "../Graph_lib/Graph.h"

using namespace Graph_lib;


class PlatformShape : public Rectangle {
public:
    PlatformShape(Platform& p);

    Platform& parent() { return platform; }

    void onPlatformMoved();

private:
    Platform& platform;
};


#endif //ARKANOID_PLATFORMSHAPE_H
