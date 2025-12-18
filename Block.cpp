#include "Block.h"
#include <FL/fl_draw.H>
#include <FL/Fl_PNG_Image.H>

Block::Block(Point xy, int width, int height, int hp) : 
    Rectangle(xy, width, height), health(hp) {
    
    int textureIndex = (xy.x / width + xy.y / height) % 4;
    
    const char* textures[] = {
        "sources/textures/roflan_block.png",
        "sources/textures/nerd_block.png",
        "sources/textures/moustache_block.png",
        "sources/textures/purple_block.png"
    };
    
    textureName = textures[textureIndex];
}

void Block::draw_lines() const {
    int x = point(0).x;
    int y = point(0).y;
    int w = width();
    int h = height();
    
    Fl_PNG_Image texture(textureName);
    
    if (texture.w() > 0) {
        texture.draw(x, y, w, h);
    } else {
        fl_color(FL_RED);
        fl_rectf(x, y, w, h);
    }
    
    fl_color(FL_BLACK);
    fl_rect(x, y, w, h);
}