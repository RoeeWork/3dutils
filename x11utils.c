#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "x11utils.h"

Display *disp;
Window win;
GC gc;

Window root;
int defaultScreen;

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

void draw_square(int x, int y) {
		XFillRectangle(disp, win, gc, x, y, 10, 10 );
		XFlush(disp);
}

void draw_line(int x1, int y1, int x2, int y2) {
	XDrawLine(disp, win, gc, x1, y1, x2, y2);
	XFlush(disp);
}
void handle_event() {
	while(XPending(disp)) {
		XEvent event;
		XNextEvent(disp, &event);
		if (event.type == KeyPress) {
			XUnmapWindow(disp, win);
			XDestroyWindow(disp, win);
			XFreeGC(disp, gc);

			XCloseDisplay(disp);
			exit(0);
		}
	}
}

void init_xlib() {
	disp = XOpenDisplay(0);
	if (disp == NULL) {
		exit(1);
	}
	root = DefaultRootWindow(disp);
	defaultScreen = DefaultScreen(disp);
	win = create_window(X, Y, WIDTH, HEIGHT, BORDER_WIDTH);
	gc = create_GC(LINE_WIDTH);
	
	XSetForeground(disp, gc, _RGB(0,255,0));
	XMapWindow(disp, win);
}
