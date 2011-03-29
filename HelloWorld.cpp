#include "HelloWorld.h"

#include <X11/Xlib.h>

#include <cstring>


const char HelloWorld::WINDOW_FONT[] = "-*-*-*-*-*-*-12-*-*-*-*-*-*-*";


HelloWorld::HelloWorld(Display* display) {
    _display = display;
    _screen = XDefaultScreenOfDisplay(display);

    _blackColor = BlackPixelOfScreen(_screen);
    _whiteColor = WhitePixelOfScreen(_screen);

    _font = XLoadFont(_display, WINDOW_FONT);

    int screenWidth = XWidthOfScreen(_screen);
    int screenHeight = XHeightOfScreen(_screen);

    int windowWidth = 300;
    int windowHeight = 375;
    int windowX = (screenWidth + windowWidth) / 2;
    int windowY = (screenHeight + windowHeight) / 2;
    _window = XCreateSimpleWindow(_display, XRootWindowOfScreen(_screen),
            windowX, windowY, windowWidth, windowHeight, 1, _blackColor,
            _whiteColor);

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
    XSetFont(_display, gc, _font);

    char* helloWorldText = "Hello, World!";
    XDrawString(_display, _window, gc, 10, 10, helloWorldText, strlen(helloWorldText));
}

void HelloWorld::map() {
    XMapWindow(_display, _window);
}
