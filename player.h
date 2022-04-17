#include <common.h>

class Player{
public:
	double x, y, dx, dy, dir;
	Player();
	void changeDir(double dir);
	void move(double sp, int d = 0);
};
