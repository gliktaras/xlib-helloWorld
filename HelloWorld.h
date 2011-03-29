#ifndef __HELLOWORLD_H__
#define __HELLOWORLD_H__

#include <X11/Xlib.h>

class HelloWorld {
public:
    HelloWorld(Display* display);

    Window getWindow();

    void draw();
    void map();

    void restartGame();
private:
    enum GAME_STATE { HUMAN_TURN, AI_TURN, HUMAN_WON, AI_WON, DRAW };

    const static int MIN_CELL_SIZE;
    const static int STRING_HEIGHT;
    const static char WINDOW_FONT[];

    Display* _display;
    Screen* _screen;
    Window _window;

    Font _font;
    unsigned long _blackColor;
    unsigned long _whiteColor;

    char _boardState[3][3];
    GAME_STATE _gameState;
    int _turnsPassed;

    void _drawO(GC* gc, int x, int y, int w, int h);
    void _drawX(GC* gc, int x, int y, int w, int h);

    void _drawString(GC* gc, char* str, int x, int y);
    void _drawStringCentered(GC* gc, char* str, int x, int y, int w, int h);
};

inline Window HelloWorld::getWindow() {
    return _window;
}

#endif //__HELLOWORLD_H__
