#include "HelloWorld.h"

#include <X11/Xlib.h>


HelloWorld::HelloWorld(Display* display) {
    this->display = display;
    screen = XDefaultScreenOfDisplay(display);

    int screenWidth = XWidthOfScreen(screen);
    int screenHeight = XHeightOfScreen(screen);

    int windowWidth = 300;
    int windowHeight = 400;
    int windowX = (screenWidth + windowWidth) / 2;
    int windowY = (screenHeight + windowHeight) / 2;

    window = XCreateSimpleWindow(display, XRootWindowOfScreen(screen),
            windowX, windowY, windowWidth, windowHeight, 1,
            BlackPixelOfScreen(screen), WhitePixelOfScreen(screen));

    long eventMask = ExposureMask;
    XSelectInput(display, window, eventMask);

    draw();
}

void HelloWorld::draw() {
    Window rootWindow;
    int x;
    int y;
    unsigned int width;
    unsigned int height;
    unsigned int borderWidth;
    unsigned int bitDepth;

    XGetGeometry(display, window, &rootWindow, &x, &y, &width, &height,
            &borderWidth, &bitDepth);

    GC gc = XDefaultGCOfScreen(screen);
    XDrawLine(display, window, gc, 0, 0, width, height);
}

void HelloWorld::map() {
    XMapWindow(display, window);
}
