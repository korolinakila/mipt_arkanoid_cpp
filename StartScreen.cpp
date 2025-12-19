#include "StartScreen.h"
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>
#include "ArkanoidWindow.h"
#include "Graph_lib/Window.h"

StartScreen::StartScreen(int x, int y, int w, int h, Graph_lib::Window& window) 
    : Fl_Group(x, y, w, h), background("sources/textures/StartScreen.png") {

    Fl_PNG_Image* button_img = new Fl_PNG_Image("sources/textures/button_start.png");
    
    Fl_Button *button = new Fl_Button(300, 350, 200, 100);
    if (button_img && !button_img->fail()) {
        button->image(button_img);

        
        button->label(nullptr);
    } else {
        button->label("СТАРТ");
        button->labelfont(FL_BOLD);
        button->labelsize(20);
        button->labelcolor(FL_WHITE);
    }
    
    button->callback([](Fl_Widget *w, void *data) {
        static_cast<ArkanoidWindow*>(data)->openGameScreen();
    }, &window);
}

void StartScreen::draw() {
    if (!background.fail()) {
        background.draw(x(), y(), w(), h());
    }
    Fl_Group::draw();
}