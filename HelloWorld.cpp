#include "HelloWorld.h"

#include <X11/Xlib.h>


HelloWorld::HelloWorld(Display* display) {
    this->display = display;

    Screen* screen = XDefaultScreenOfDisplay(display);
    int screenWidth = XWidthOfScreen(screen);
    int screenHeight = XHeightOfScreen(screen);

    int windowWidth = 300;
    int windowHeight = 400;
    int windowX = (screenWidth + windowWidth) / 2;
    int windowY = (screenHeight + windowHeight) / 2;

    window = XCreateSimpleWindow(display, XRootWindowOfScreen(screen),
            windowX, windowY, windowWidth, windowHeight, 1,
            BlackPixelOfScreen(screen), WhitePixelOfScreen(screen));
}

void HelloWorld::map() {
    XMapWindow(display, window);
}
