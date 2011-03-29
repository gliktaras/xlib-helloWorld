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
    XSetBackground(_display, gc, _whiteColor);
    XSetFont(_display, gc, _font);
    XSetForeground(_display, gc, _blackColor);

    if((width < 150) || (height < 225)) {
        _drawStringCentered(&gc, "Window too small.", 0, 0, width, height);
        return;
    }

    _drawStringCentered(&gc, "Hello, World!", 0, 0, width, 25);
    _drawStringCentered(&gc, "Tic-tac-toe message here.", 0, 25, width, 25);
    _drawStringCentered(&gc, "[R]estart, [Q]uit.", 0, height - 25, width, 25);
}

void HelloWorld::map() {
    XMapWindow(_display, _window);
}


void HelloWorld::_drawString(GC* gc, char* str, int x, int y) {
    XDrawString(_display, _window, *gc, x, y, str, strlen(str));
}

void HelloWorld::_drawStringCentered(GC* gc, char* str, int x, int y, int w,
                                     int h) {
    int direction, ascent, descent;
    XCharStruct strDimensions;
    XTextExtents(XQueryFont(_display, XGContextFromGC(*gc)), str, strlen(str),
            &direction, &ascent, &descent, &strDimensions);

    int newX = x + (w - strDimensions.width) / 2;
    int newY = y + (h + strDimensions.ascent - strDimensions.descent) / 2;
    _drawString(gc, str, newX, newY);
}
