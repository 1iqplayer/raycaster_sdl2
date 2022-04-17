#include <common.h>
#include <player.h>
#include <math.h>

Player::Player(){
	dir = PI/2;
	dx = cos(dir) * 10;
	dy = sin(dir) * 10;
}
void Player::changeDir(double d){
	dir += d;
	if (dir > PI*2) dir = dir - PI*2;
	if (dir < 0.0f) dir = dir + PI*2;

	dx = cos(dir) * 15;
	dy = sin(dir) * 15;
}
void Player::move(double sp, int d){
	double _dir = 0.0;
	if (d == 1)
		_dir = PI/2;
	if (d == 2)
		_dir = PI;
	if (d == 3)
		_dir = 1.5 * PI;
	_dir = dir + _dir;
	// normalizing _dir
	if (_dir > PI*2) _dir = _dir - PI*2; if (_dir < 0) _dir = _dir + PI*2;

	x += cos(_dir) * sp;
	y += sin(_dir) * sp;
}
