#include "PlatformShape.h"

using namespace Graph_lib;


PlatformShape::PlatformShape(Platform &p) :
        Rectangle(Point{p.getX(), p.getY()}, p.getWidth(), p.getHeight()),
        platform{p} {
    platform.setCallback([this]() { this->onPlatformMoved(); });
}

void PlatformShape::onPlatformMoved() {
    Shape::set_point(0, Point{platform.getX(), platform.getY()});
}