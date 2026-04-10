#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>

/*
functions:
	- XOpenDisplay
	- DefaultRootWindow
	- DefaultScreen
	- XMatchVisualInfo
*/

int main(int argc, char **argv) {
	Display* display = XOpenDisplay(0);
	if (!display) {
		fprintf(stderr, "cant open display!");
		exit(1);
	}

	int root = DefaultRootWindow(display);
	int defaultScreen = DefaultScreen(display);

	int screenBitDepth = 24;
	XVisualInfo visual_info = {};
	XGetVisualInfo(display, defaultScreen, screenBitDepth, TrueColor, &visual_info);

}
