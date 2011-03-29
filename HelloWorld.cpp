#include "HelloWorld.h"

#include <X11/Xlib.h>


HelloWorld::HelloWorld(Display* display) {
    _display = display;
    _screen = XDefaultScreenOfDisplay(display);

    int screenWidth = XWidthOfScreen(_screen);
    int screenHeight = XHeightOfScreen(_screen);

    int windowWidth = 300;
    int windowHeight = 400;
    int windowX = (screenWidth + windowWidth) / 2;
    int windowY = (screenHeight + windowHeight) / 2;

    _window = XCreateSimpleWindow(_display, XRootWindowOfScreen(_screen),
            windowX, windowY, windowWidth, windowHeight, 1,
            BlackPixelOfScreen(_screen), WhitePixelOfScreen(_screen));

    long eventMask = ExposureMask;
    XSelectInput(_display, _window, eventMask);

    draw();
}

void HelloWorld::draw() {
    Window rootWindow;
    int x, y;
    unsigned int width, height, borderWidth, bitDepth;
    XGetGeometry(_display, _window, &rootWindow, &x, &y, &width, &height,
            &borderWidth, &bitDepth);

    GC gc = XDefaultGCOfScreen(_screen);
    XDrawLine(_display, _window, gc, 0, 0, width, height);
}

void HelloWorld::map() {
    XMapWindow(_display, _window);
}
