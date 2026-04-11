#include "x11utils.h"

struct Point3d {
	float x;
	float y;
	float z;
};

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


struct Point3d points[8] = {
	{0.25, 0.25, 	0.25},
	{-0.25, 0.25, 	0.25},
	{0.25, -0.25, 	0.25},
	{-0.25, -0.25, 	0.25},

	{0.25, 0.25, 	-0.25},
	{-0.25, 0.25, 	-0.25},
	{0.25, -0.25, 	-0.25},
	{-0.25, -0.25, 	-0.25}
};

struct Point3d translate_z( struct Point3d p, float dz) {
	struct Point3d n = {p.x, p.y, p.z += dz};
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

	struct Point3d npoints[8];

	//dz += v*dt;
	angle += 3.14*dt;
	for (int i = 0; i < 8; i++) {
		npoints[i] = screen(project(translate_z(rotate_xz(points[i], angle), dz)));
	}

	fprintf(stdout, "dt = %f\n", dt);
	fprintf(stdout, "dz = %f*%f = %f\n",v, dt, dz);

	XClearWindow(disp,win);
	for (int j = 0; j < 8; j++) {
		struct Point3d pn = npoints[j];
		draw_square(pn.x - 5, pn.y - 5);
		fprintf(stdout, "points[%d]: (%f, %f, %f)\n", j, pn.x, pn.y, pn.z);
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
