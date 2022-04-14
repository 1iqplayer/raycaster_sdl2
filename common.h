#ifndef COMMON
#define COMMON
const double PI = 3.14159265359;
const double fov = PI * 0.35;
const float fps = 1000 / 60;
struct dVec
{
	double x = 0.0, y = 0.0;
};
struct iVec
{
	int x = 0, y = 0;
};
const int WIDTH = 800,
		  HEIGHT = 500,
		  RES_W = 100,
		  MAP_W = 10,
		  MAP_H = 10,
		  GRID_SIZE = 40;
const bool map[] = {
1,1,1,1,1,0,0,0,0,0,
1,0,0,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,1,0,0,0,1,
1,1,1,0,0,1,0,0,0,1,
1,0,0,0,0,1,0,0,0,1,
1,0,0,0,0,1,1,1,1,1,
1,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,1
};
#endif