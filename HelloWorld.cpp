#include "HelloWorld.h"

#include <X11/Xlib.h>

#include <cstring>


const int HelloWorld::MIN_CELL_SIZE = 50;
const int HelloWorld::STRING_HEIGHT = 20;
const char HelloWorld::WINDOW_FONT[] = "-*-*-*-*-*-*-12-*-*-*-*-*-*-*";


HelloWorld::HelloWorld(Display* display) {
    _display = display;
    _screen = XDefaultScreenOfDisplay(display);

    _blackColor = BlackPixelOfScreen(_screen);
    _whiteColor = WhitePixelOfScreen(_screen);

    _font = XLoadFont(_display, WINDOW_FONT);

    int screenWidth = XWidthOfScreen(_screen);
    int screenHeight = XHeightOfScreen(_screen);

    int windowWidth = MIN_CELL_SIZE * 3;
    int windowHeight = MIN_CELL_SIZE * 3 + STRING_HEIGHT * 3;
    int windowX = (screenWidth + windowWidth) / 2;
    int windowY = (screenHeight + windowHeight) / 2;
    _window = XCreateSimpleWindow(_display, XRootWindowOfScreen(_screen),
            windowX, windowY, windowWidth, windowHeight, 1, _blackColor,
            _whiteColor);

    long eventMask = ExposureMask;
    XSelectInput(_display, _window, eventMask);

    restartGame();
    draw();
}


void HelloWorld::draw() {
    // Getting window dimensions.
    Window rootWindow;
    int x, y;
    unsigned int width, height, borderWidth, bitDepth;
    XGetGeometry(_display, _window, &rootWindow, &x, &y, &width, &height,
            &borderWidth, &bitDepth);

    // Setting up the GC.
    GC gc = XDefaultGCOfScreen(_screen);
    XSetBackground(_display, gc, _whiteColor);
    XSetFont(_display, gc, _font);
    XSetForeground(_display, gc, _blackColor);

    // Is the window large enough for us?
    if((width < MIN_CELL_SIZE * 3) ||
            (height < (MIN_CELL_SIZE * 3 + STRING_HEIGHT * 3))) {
        _drawStringCentered(&gc, "Window too small.", 0, 0, width, height);
        return;
    }

    // Draw the grid lines.
    int xStepSize = width / 3;
    int yStepSize = (height - STRING_HEIGHT * 3) / 3;
    for(int i = 0; i <= 3; i++) {
        int yValue = STRING_HEIGHT * 2 + yStepSize * i;
        XDrawLine(_display, _window, gc, 0, yValue, width, yValue);
    }
    for(int i = 1; i <= 2; i++) {
        int xValue = xStepSize * i;
        XDrawLine(_display, _window, gc, xValue, STRING_HEIGHT * 2, xValue,
                height - STRING_HEIGHT);
    }

    // Draw the strings.
    _drawStringCentered(&gc, "Hello, World!", 0, 0, width, STRING_HEIGHT);
    _drawStringCentered(&gc, "[R]estart, [Q]uit.", 0, height - STRING_HEIGHT,
            width, STRING_HEIGHT);

    switch(_gameState) {
    case HUMAN_TURN:
        _drawStringCentered(&gc, "It is your turn to play.", 0, STRING_HEIGHT,
                width, STRING_HEIGHT);
        break;
    case AI_TURN:
        _drawStringCentered(&gc, "Please wait, thinking...", 0, STRING_HEIGHT,
                width, STRING_HEIGHT);
        break;
    case HUMAN_WON:
        _drawStringCentered(&gc, "You have won.", 0, STRING_HEIGHT, width,
                STRING_HEIGHT);
        break;
    case AI_WON:
        _drawStringCentered(&gc, "You have lost.", 0, STRING_HEIGHT, width,
                STRING_HEIGHT);
        break;
    case DRAW:
        _drawStringCentered(&gc, "It is a draw.", 0, STRING_HEIGHT, width,
                STRING_HEIGHT);
        break;
    default:
        break;
    }
}

void HelloWorld::map() {
    XMapWindow(_display, _window);
}


void HelloWorld::restartGame() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            _boardState[i][j] = ' ';
        }
    }
    _gameState = HUMAN_TURN;
    _turnsPassed = 0;
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
