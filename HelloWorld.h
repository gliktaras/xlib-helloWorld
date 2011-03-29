#ifndef __HELLOWORLD_H__
#define __HELLOWORLD_H__

#include "Game.h"

#include <X11/Xlib.h>

class HelloWorld {
public:
    HelloWorld(Display* display);

    Window getWindow();

    void draw();
    void map();

    void handleKeyPress(unsigned int mod, unsigned int keycode);
    void restartGame();
private:
    const static int MIN_CELL_SIZE;
    const static int STRING_HEIGHT;
    const static char WINDOW_FONT[];

    Display* _display;
    Screen* _screen;
    Window _window;

    Font _font;
    unsigned long _blackColor;
    unsigned long _whiteColor;

    Game _game;

    void _drawO(GC* gc, int x, int y, int w, int h);
    void _drawX(GC* gc, int x, int y, int w, int h);

    void _drawString(GC* gc, char* str, int x, int y);
    void _drawStringCentered(GC* gc, char* str, int x, int y, int w, int h);
};

inline Window HelloWorld::getWindow() {
    return _window;
}

#endif //__HELLOWORLD_H__
