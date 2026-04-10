#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>


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

	 Window win;

	 XEvent event;

	 char* disp_name;
	 display = XOpenDisplay(0);
	 int root = DefaultRootWindow(display);
	 int defaultScreen = DefaultScreen(display);

	 GC gc = DefaultGC(display, 0);

	 int screenBitDepth = 24;
	 XVisualInfo visinfo = {};
	 if(!XMatchVisualInfo(display, defaultScreen, screenBitDepth, TrueColor, &visinfo))
	 {
		 printf("No matching visual info\n");
		 exit(1);
	 }

	 XSetWindowAttributes  windowattrs;
	 windowattrs.background_pixel = 0;
	 windowattrs.colormap = XCreateColormap(display, root, visinfo.visual, AllocNone);
	 unsigned long attrMask = CWBackPixel | CWColormap;

     win = XCreateSimpleWindow(display, root, 0, 0, 100, 100, 2, visinfo.depth, InputOutput, visinfo.visual, attrMask, &windowattrs);

	 XMapWindow(display, win);
	 XSelectInput(display, win, KeyPressMask | ExposureMask);
	
	 for(;;) {
		XNextEvent(display, &event);
		if (event.type == Expose) {
	 		XDrawString(display, win, gc, 10, 20, "press key pls", 20);
			XDrawRectangle(display, win, gc, 20, 30, 40, 40 );
			XFillRectangle(display, win, gc, 20, 30, 40, 40 );
		}
		if (event.type == KeyPress) {
			XCloseDisplay(display);
			exit(0);
		}
	 }
	 return 0;
}
