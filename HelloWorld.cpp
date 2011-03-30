#include "Game.h"
#include "HelloWorld.h"

#include <X11/Xlib.h>
#include <X11/keysym.h>

#include <cstring>


const int HelloWorld::MIN_CELL_SIZE = 50;
const int HelloWorld::STRING_HEIGHT = 20;
const char HelloWorld::WINDOW_FONT[] = "-*-*-*-*-*-*-12-*-*-*-*-*-*-*";


HelloWorld::HelloWorld(Display* display) :
    _game() {

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

    long eventMask = ButtonPressMask | ExposureMask | KeyPressMask;
    XSelectInput(_display, _window, eventMask);

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

    // Clearing the window.
    XClearArea(_display, _window, 0, 0, width, height, false);

    // Is the window large enough for us?
    if((width < MIN_CELL_SIZE * 3) ||
            (height < (MIN_CELL_SIZE * 3 + STRING_HEIGHT * 3))) {
        _drawStringCentered(&gc, "Window too small.", 0, 0, width, height);
        return;
    }

    // Calculating grid cell sizes.
    int xStepSize = width / 3;
    int yStepSize = (height - STRING_HEIGHT * 3) / 3;

    // Drawing glyphs.
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            switch(_game.getCellState(i, j)) {
            case CELL_O:
                _drawO(&gc, xStepSize * i, STRING_HEIGHT * 2 + yStepSize * j,
                        xStepSize, yStepSize);
                break;
            case CELL_X:
                _drawX(&gc, xStepSize * i, STRING_HEIGHT * 2 + yStepSize * j,
                        xStepSize, yStepSize);
                break;
            default:
                break;
            }
        }
    }
    XSetBackground(_display, gc, _whiteColor);
    XSetForeground(_display, gc, _blackColor);

    // Drawing the grid lines.
    for(int i = 0; i <= 3; i++) {
        int yValue = STRING_HEIGHT * 2 + yStepSize * i;
        XDrawLine(_display, _window, gc, 0, yValue, width, yValue);
    }
    for(int i = 1; i <= 2; i++) {
        int xValue = xStepSize * i;
        XDrawLine(_display, _window, gc, xValue, STRING_HEIGHT * 2, xValue,
                height - STRING_HEIGHT);
    }

    // Drawing the strings.
    _drawStringCentered(&gc, "Hello, World!", 0, 0, width, STRING_HEIGHT);
    _drawStringCentered(&gc, "[R]estart", 0, height - STRING_HEIGHT,
            width, STRING_HEIGHT);

    switch(_game.getGameState()) {
    case X_TURN:
        _drawStringCentered(&gc, "It is your turn to play.", 0, STRING_HEIGHT,
                width, STRING_HEIGHT);
        break;
    case O_TURN:
        _drawStringCentered(&gc, "Please wait, thinking...", 0, STRING_HEIGHT,
                width, STRING_HEIGHT);
        break;
    case X_WON:
        _drawStringCentered(&gc, "You have won.", 0, STRING_HEIGHT, width,
                STRING_HEIGHT);
        break;
    case O_WON:
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

void HelloWorld::handleKeyPress(unsigned int state, unsigned int keycode) {
    unsigned int keyCode_r = XKeysymToKeycode(_display, XK_r);
    unsigned int keyCode_q = XKeysymToKeycode(_display, XK_q);

    if(keycode == keyCode_r) {
        _game.restart();
        draw();
    } else if(keycode == keyCode_q) {
        // Quit, somehow
    }
}

void HelloWorld::handleMousePress(int x, int y, unsigned int state,
                                  unsigned int button) {
    if(button == 1) {
        Window rootWindow;
        int winX, winY;
        unsigned int width, height, borderWidth, bitDepth;
        XGetGeometry(_display, _window, &rootWindow, &winX, &winY, &width,
                &height, &borderWidth, &bitDepth);

        if((y >= 2 * STRING_HEIGHT) && (y < (height - STRING_HEIGHT))) {
            int xStepSize = width / 3;
            int yStepSize = (height - STRING_HEIGHT * 3) / 3;

            int cellX = x / xStepSize;
            int cellY = (y - STRING_HEIGHT * 2) / yStepSize;

            if(_game.makeMove(cellX, cellY)) {
                _game.makeRandomMove();
                draw();
            }
        }
    }
}

void HelloWorld::restartGame() {
    _game.restart();
    draw();
}


void HelloWorld::_drawO(GC* gc, int x, int y, int w, int h) {
    XSetBackground(_display, *gc, _whiteColor);
    XSetForeground(_display, *gc, _blackColor);
    XFillArc(_display, _window, *gc, x + w/10, y + h/10, (w*4)/5, (h*4)/5, 0,
            360*64);

    XSetForeground(_display, *gc, _whiteColor);
    XFillArc(_display, _window, *gc, x + w/5, y + h/5, (w*3)/5, (h*3)/5, 0,
            360*64);
}

void HelloWorld::_drawX(GC* gc, int x, int y, int w, int h) {
    static const int POINT_COUNT = 12;
    static const XPoint RAW_CROSS[] = { {1, 2}, {2, 1}, {5, 4}, {8, 1}, {9, 2},
            {6, 5}, {9, 8}, {8, 9}, {5, 6}, {2, 9}, {1, 8}, {4, 5} };

    XPoint scaledCross[POINT_COUNT];
    for(int i = 0; i < POINT_COUNT; i++) {
        scaledCross[i].x = (RAW_CROSS[i].x * w) / 10 + x;
        scaledCross[i].y = (RAW_CROSS[i].y * h) / 10 + y;
    }

    XSetBackground(_display, *gc, _whiteColor);
    XSetForeground(_display, *gc, _blackColor);
    XFillPolygon(_display, _window, *gc, scaledCross, POINT_COUNT, Nonconvex,
            CoordModeOrigin);
}


void HelloWorld::_drawString(GC* gc, const char* str, int x, int y) {
    XDrawString(_display, _window, *gc, x, y, str, strlen(str));
}

void HelloWorld::_drawStringCentered(GC* gc, const char* str, int x, int y,
                                     int w, int h) {
    int direction, ascent, descent;
    XCharStruct strDimensions;
    XTextExtents(XQueryFont(_display, XGContextFromGC(*gc)), str, strlen(str),
            &direction, &ascent, &descent, &strDimensions);

    int newX = x + (w - strDimensions.width) / 2;
    int newY = y + (h + strDimensions.ascent - strDimensions.descent) / 2;
    _drawString(gc, str, newX, newY);
}
