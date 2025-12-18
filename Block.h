#ifndef ARKANOID_BLOCK_H
#define ARKANOID_BLOCK_H

#include "Graph_lib/Graph.h"
#include <string>

using namespace Graph_lib;

class Block : public Rectangle {
public:
    Block(Point xy, int width, int height, int hp);
    
    void draw_lines() const override;
    int get_health() const;
    void set_health(int new_health);
    void deal_damage();
    
private:
    int health;
    const char* textureName; // Храним имя текстуры для этого блока
};

#endif // ARKANOID_BLOCK_H