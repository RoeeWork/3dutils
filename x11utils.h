#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define X 0
#define Y 0
#define WIDTH 400
#define HEIGHT 400
#define BORDER_WIDTH 2
#define LINE_WIDTH 4

extern Display *disp;
extern Window win;
extern GC gc;

extern Window root;
extern int defaultScreen;

unsigned long _RGB(int r,int g, int b);
Window create_window(int x, int y, int w, int h, int b);
GC create_GC(int line_width);
void draw_square(int x, int y);
