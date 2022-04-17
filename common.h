#ifndef COMMON
#define COMMON
const double PI = 3.14159265359;
const double fov = PI * 0.42;
const float fps = 1000 / 30;
struct dVec
{
	double x = 0.0, y = 0.0;
};
struct iVec
{
	int x = 0, y = 0;
};
struct ray
{
	double dist;
	bool vertical;
};
const int WIDTH = 800,
		  HEIGHT = 500,
		  MAP_W = 15,
		  MAP_H = 10,
		  GRID_SIZE = 40;
const bool map[] = {
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,1,0,0,0,1,1,0,0,
1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,0,0,1,0,0,0,1,1,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,0,0,0,0,0
};
#endif