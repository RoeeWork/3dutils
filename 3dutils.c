#include "x11utils.h"
#include "model.h"

int point_count = sizeof(points) / sizeof(points[0]);
int edge_count  = sizeof(edges)  / sizeof(edges[0]);

struct Point3d screen(struct Point3d p) { 
	struct Point3d pn;
	XWindowAttributes attrs;
    XGetWindowAttributes(disp, win, &attrs);
	pn.x = ((p.x+1)/2)*attrs.width;
	pn.y = (1 - ((p.y+1)/2))*attrs.height;
	pn.z = p.z;
	return pn;
}
struct Point3d project(struct Point3d p) { 
	struct Point3d pn;
	pn.x = p.x/p.z;
	pn.y = p.y/p.z;
	pn.z = p.z;
	return pn;
}


//struct Point3d points[8] = {
//	{0.25, 0.25, 	0.25},
//	{-0.25, 0.25, 	0.25},
//	{-0.25, -0.25, 	0.25},
//	{0.25, -0.25, 	0.25},
//
//	{0.25, 0.25, 	-0.25},
//	{-0.25, 0.25, 	-0.25},
//	{-0.25, -0.25, 	-0.25},
//	{0.25, -0.25, 	-0.25}
//};

int vp[2][4] = {
	{0, 1, 2, 3},
	{4, 5, 6, 7}
};
int vs[4][2] = {
	{0, 4},
	{1, 5},
	{2, 6},
	{3, 7}
};

struct Point3d translate_z( struct Point3d p, float dz) {
	struct Point3d n = {p.x, p.y, p.z += dz};
	return n;
}
struct Point3d translate( struct Point3d p, float dx, float dy, float dz) {
	struct Point3d n = {p.x + dx, p.y + dy, p.z += dz};
	return n;
}
struct Point3d translate_y( struct Point3d p, float dy) {
	struct Point3d n = {p.x, p.y += dy, p.z};
	return n;
}

#define FPS 60

struct Point3d rotate_xz( struct Point3d p, double angle) {
	// x = xcos(angle) - zsin(angle)
	// z = xcos(angle) + zsin(angle)
	double s = sin(angle);
	double c = cos(angle);
	struct Point3d pn = {p.x*c - p.z*s, p.y, p.x*s + p.z*c};
	return pn;
}

double dz = 1;
double dt = 1.0/FPS;
double v = 0.5;
double angle = 0;

void frame() {
	handle_event();

	struct Point3d npoints[point_count];

	//dz += v*dt;
	angle += 3.14*dt;
	for (int i = 0; i < point_count; i++) {
		npoints[i] = screen(project(translate(rotate_xz(points[i], angle), 0, -0.5, dz)));
		fprintf(stdout, "point[%d]: (%f, %f, %f)\n", i, npoints[i].x,  npoints[i].y, npoints[i].z);
	}


//	for (int j = 0; j < point_count; j++) {
//		struct Point3d pn = npoints[j];
//		draw_square(pn.x - 5, pn.y - 5);
//		fprintf(stdout, "points[%d]: (%f, %f, %f)\n", j, pn.x, pn.y, pn.z);
//	}

	XClearWindow(disp,win);
	for (int i = 0; i < edge_count; i++) {
		int a = edges[i][0];
		int b = edges[i][1];

		draw_line(
			npoints[a].x, npoints[a].y,
			npoints[b].x, npoints[b].y
		);
	}
	usleep((1000/FPS) * 1000);
}

int main() {
	init_xlib();
	for (;;) {
		frame();
	}
	return 1;
}
