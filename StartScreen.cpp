#include "StartScreen.h"
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>
#include "ArkanoidWindow.h"
#include "Graph_lib/Window.h"

StartScreen::StartScreen(int x, int y, int w, int h, Graph_lib::Window& window) 
    : Fl_Group(x, y, w, h), background_img("sources/textures/StartScreen.png") {
    
    Fl_Button *button = new Fl_Button(300, 350, 200, 100, "СТАРТ");
    button->callback([](Fl_Widget *w, void *data) {
        static_cast<ArkanoidWindow*>(data)->openGameScreen();
    }, &window);
}

void StartScreen::draw() {
    // Рисуем фон
    if (!background_img.fail()) {
        background_img.draw(x(), y(), w(), h());
    }
    // Рисуем остальные виджеты (кнопку)
    Fl_Group::draw();
}