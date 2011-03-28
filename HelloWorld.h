#ifndef __HELLOWORLD_H__
#define __HELLOWORLD_H__

#include <X11/Xlib.h>

class HelloWorld {
public:
    HelloWorld(Display* display);

    void map();
private:
    Display* display;
    Window window;
};

#endif //__HELLOWORLD_H__
