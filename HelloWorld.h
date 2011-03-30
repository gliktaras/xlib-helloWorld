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

    void handleKeyPress(unsigned int state, unsigned int keycode);
    void handleMousePress(int x, int y, unsigned int state,
            unsigned int button);
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

    void _drawO(const GC& gc, int x, int y, int w, int h);
    void _drawX(const GC& gc, int x, int y, int w, int h);

    void _drawString(const GC& gc, const char* str, int x, int y);
    void _drawStringCentered(const GC& gc, const char* str, int x, int y, int w, int h);
};

inline Window HelloWorld::getWindow() {
    return _window;
}

#endif //__HELLOWORLD_H__
