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

    XSync(display, false);
    while(true);

    XCloseDisplay(display);
    return 0;
}
