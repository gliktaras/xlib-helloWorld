#ifndef __HELLOWORLD_H__
#define __HELLOWORLD_H__

#include <X11/Xlib.h>

class HelloWorld {
public:
    HelloWorld(Display* display);

    Window getWindow();

    void draw();
    void map();
private:
    Display* _display;
    Screen* _screen;
    Window _window;
};

inline Window HelloWorld::getWindow() {
    return _window;
}

#endif //__HELLOWORLD_H__
