#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <X11/Xlib.h>

struct window_info {
	Display *display;
	int screen_num;
	int win_width;
	int win_height;
	int win_x;
	int win_y;
	int win_border_size;
};

Display *CreateDisplay() {
	char *display_name = getenv("DISPLAY");
	Display *disp = XOpenDisplay(display_name);
	if (disp== NULL) {
		fprintf(stderr, "Cannot connect to x server %s", "roee:0");
		exit(-1);
	}
	return disp;
}

void init_window(struct window_info *info) {
	info->display = CreateDisplay();
	info->screen_num = DefaultScreen(info->display);
	info->win_width = DisplayWidth(info->display, info->screen_num) /3;
	info->win_height = DisplayHeight(info->display, info->screen_num) /3;
	info->win_x = 0;
	info->win_y = 0;
	info->win_border_size = 1;
}
Window CreateWindow(struct window_info info) {
	
	int win_border_size = 2;
	Window win = XCreateSimpleWindow(info.display,
							  RootWindow(info.display, info.screen_num),
							  info.win_x, info.win_y,
							  info.win_width, info.win_height,
							  info.win_border_size,
							  BlackPixel(info.display, info.screen_num),
							  WhitePixel(info.display, info.screen_num)
			);
	XMapWindow(info.display, win);
	XSync(info.display, win);
	return win;
}
int main(int argc, char* argv[]) {
	Window win;
	struct window_info win_info;
	init_window(&win_info);

	win = CreateWindow(win_info);
	sleep(4);
	return -1;
}
