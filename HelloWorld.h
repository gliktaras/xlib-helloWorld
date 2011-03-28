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
    Display* display;
    Screen* screen;
    Window window;
};

inline Window HelloWorld::getWindow() {
    return window;
}

#endif //__HELLOWORLD_H__
