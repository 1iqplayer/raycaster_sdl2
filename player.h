#include <common.h>

class Player{
public:
	float x, y, dx, dy, speed;
	double dir;
	Player();
	void changeDir(double dir);
};
