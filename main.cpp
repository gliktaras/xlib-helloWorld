#include "HelloWorld.h"

#include <X11/Xlib.h>

#include <iostream>
#include <cstdlib>

using std::endl;
using std::cerr;


int main() {
    Display* display = XOpenDisplay(NULL);
    if(!display) {
        cerr << "Unable to connect to X server." << endl;
        exit(1);
    }

    HelloWorld mainWindow(display);
    mainWindow.map();

    XFlush(display);

    XEvent event;
    while(true) {
        XNextEvent(display, &event);

        switch(event.type) {
        case ButtonPress:
            mainWindow.handleMousePress((XButtonEvent)event.xbutton);
        case Expose:
            if(event.xexpose.count == 0) {
                mainWindow.draw();
            }
            break;
        case KeyPress:
            mainWindow.handleKeyPress((XKeyEvent)event.xkey);
        default:
            break;
        }
    }

    XCloseDisplay(display);
    return 0;
}
