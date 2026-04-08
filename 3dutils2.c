#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>

/*
functions:
	- XOpenDisplay
	- XDisplayName
	- XRootWindow
	- XCreateSimpleWindow
	- XMapWindow
	- DefaultRootWindow
	- BlackPixel
	- WhitePixel
	- XSelectInput
	- XNextEvent
	- XEvent
*/

int main(int argc, char **argv) {
     Display *display;

	 Window parent;
	 Window win;

	 XEvent event;

	 char* disp_name;
	 disp_name = getenv("DISPLAY");
	 display = XOpenDisplay(disp_name);
	 parent = DefaultRootWindow(display);

	 GC gc = DefaultGC(display, 0);

     win = XCreateSimpleWindow(display, parent,
			 0, 0,
			 100, 100,
			 2, BlackPixel(display, 0),
			 WhitePixel(display, 0));

	 XMapWindow(display, win);
	 XSelectInput(display, win, KeyPressMask | ExposureMask);
	
	 for(;;) {
		XNextEvent(display, &event);
		if (event.type == Expose) {
	 		XDrawString(display, win, gc, 10, 20, "press key pls", 20);
			XDrawRectangle(display, win, gc, 20, 30, 40, 40 );
		}
		if (event.type == KeyPress) {
			XCloseDisplay(display);
			exit(0);
		}
	 }
	 return 0;
}
