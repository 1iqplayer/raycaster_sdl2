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
void Player::move(double sp){
	x += cos(dir) * sp;
	y += sin(dir) * sp;
}
