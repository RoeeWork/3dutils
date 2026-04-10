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

Display *disp;
Window win;
GC gc;

Window root;
int defaultScreen;

#define X 0
#define Y 0
#define WIDTH 400
#define HEIGHT 400
#define BORDER_WIDTH 2
#define LINE_WIDTH 4

unsigned long _RGB(int r,int g, int b)
{
    return b + (g<<8) + (r<<16);
}

Window create_window(int x, int y, int w, int h, int b) {

	 XSetWindowAttributes  winattrs;

	 winattrs.background_pixel = BlackPixel(disp, defaultScreen);
	 winattrs.border_pixel = WhitePixel(disp, defaultScreen);
	 winattrs.event_mask = KeyPressMask | ExposureMask;

	 int attrMask = CWBackPixel | CWBorderPixel | CWEventMask;

     win = XCreateWindow(disp, root,
		 					x, y, w, h,
							b, DefaultDepth(disp, defaultScreen),
							InputOutput, DefaultVisual(disp, defaultScreen),
							attrMask, &winattrs);
	 return win;
}

GC create_GC(int line_width) {
	XGCValues gcvals;
	unsigned long valmask;

	gcvals.line_style = LineSolid;
	gcvals.line_width = line_width;
	gcvals.cap_style = CapButt;
	gcvals.join_style = JoinMiter;
	gcvals.fill_style = FillSolid;
	gcvals.background = BlackPixel(disp, defaultScreen); 
	gcvals.foreground = WhitePixel(disp, defaultScreen); 

	valmask = GCForeground | GCBackground 
				| GCLineWidth | GCLineStyle
				| GCCapStyle | GCJoinStyle
				| GCFillStyle;

	return XCreateGC(disp, win, valmask, &gcvals);
}

void run(GC gc) {
	XEvent event;
	//XSelectInput(disp, win, KeyPressMask | ExposureMask);

	for(;;) {
		XNextEvent(disp, &event);
		if (event.type == Expose) {
			XSetForeground(disp, gc, _RGB(255,0,0));
			XDrawString(disp, win, gc, 10, 20, "press key pls", 20);
			XFillRectangle(disp, win, gc, 20, 20, 40, 40 );
		}
		if (event.type == KeyPress) {
			XUnmapWindow(disp, win);
			XDestroyWindow(disp, win);
			XFreeGC(disp, gc);

			XCloseDisplay(disp);
			exit(0);
		}
	 }
}

int main() {
	disp = XOpenDisplay(0);
	if (disp == NULL) {
		exit(1);
	}
	root = DefaultRootWindow(disp);
	defaultScreen = DefaultScreen(disp);
	win = create_window(X, Y, WIDTH, HEIGHT, BORDER_WIDTH);
	gc = create_GC(LINE_WIDTH);
	
	XMapWindow(disp, win);
	run(gc);

	return 1;
}
