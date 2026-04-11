#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define X 0
#define Y 0
#define WIDTH 952
#define HEIGHT 1012
#define BORDER_WIDTH 2
#define LINE_WIDTH 4

extern Display *disp;
extern Window win;
extern GC gc;

extern Window root;
extern int defaultScreen;

struct Point3d;

unsigned long _RGB(int r,int g, int b);
Window create_window(int x, int y, int w, int h, int b);
GC create_GC(int line_width);
void draw_square(int x, int y);
void handle_event();
void init_xlib();
void draw_line(int x1, int y1, int x2, int y2);
