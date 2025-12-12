#include "StartScreen.h"
#include "Fl/Fl_Group.H"
#include "FL/Fl_Button.H"
#include "ArkanoidWindow.h"
#include "Graph_lib/Window.h"


StartScreen::StartScreen(int x, int y, int w, int h, Graph_lib::Window& window) : Fl_Group(x, y, w, h) {
    Fl_Button *button = new Fl_Button(300, 350, 200, 100, "СТАРТ");
    button->callback([](Fl_Widget *w, void *data) {
        static_cast<ArkanoidWindow*>(data)->openGameScreen();
    }, &window);
}