#include <SDL2/SDL.h>
#include <renderer.h>
#include <common.h>
#include <stdio.h>>
#include <math.h>
double castRay(double x, double y, double dir){
	dVec start, rayLen, rayDir, scale;
	iVec mapCheck, step;
	mapCheck.x = int(x); mapCheck.y = int(y); // Integer value of position in map
	
	// Calculate ray direction vector
	rayDir.x = cos(dir);  rayDir.y = sin(dir);
	// Calculate step size in each direction
	scale.x = sqrt(1 + (rayDir.y*rayDir.y)/(rayDir.x*rayDir.x));  
	scale.y = sqrt(1 + (rayDir.x*rayDir.x)/(rayDir.y*rayDir.y));
	// Define stepping direction and inital rayLen
	if (rayDir.x < 0)
	{
		step.x = -1;
		rayLen.x = (x - double(mapCheck.x)) * scale.x;
	}else
	{
		step.x = 1;
		rayLen.x = (double(mapCheck.x + 1) - x) * scale.x;
	}
	if (rayDir.y < 0)
	{
		step.y = -1;
		rayLen.y = (y - double(mapCheck.y)) * scale.y;
	}else
	{
		step.y = 1;
		rayLen.y = (double(mapCheck.y + 1) - y) * scale.y;
	}
	printf("intial len x:%f  y:%f\n",rayLen.x, rayLen.y );
	printf("pos x:%f y%f\n", x, y);
	// Walking
	double maxDistance = 100.0;
	double distance = 0.0;
	bool hit = false;

	while (!hit and distance < maxDistance)
	{
		if (rayLen.x < rayLen.y)
		{
			mapCheck.x += step.x;
			distance = rayLen.x;
			rayLen.x += scale.x;
		}
		else
		{
			mapCheck.y += step.y;
			distance = rayLen.y;
			rayLen.y += scale.y;
		}

		if (mapCheck.x < MAP_W and mapCheck.x >= 0 and mapCheck.y < MAP_H and mapCheck.y >= 0)
		{
			if (map[mapCheck.y*MAP_W + mapCheck.x]) 
				hit = true;

			//printf("collided with x:%i  y:%i\n", mapCheck.x, mapCheck.y);
		}
	}

	printf("scale x: %f  y:%f\nstep x: %i  y:%i\n distance: %f\n", scale.x, scale.y, step.x, step.y, distance);

	// Endpoint vector
	return distance;
}
Render::Render(SDL_Window *w){
	renderer = SDL_CreateRenderer(w, -1, 0);
}

void Render::drawWall(int x, int s){
	SDL_Rect wallRect;
	//wallRect.x = x * (WIDTH/RES_W);
	wallRect.y = HEIGHT/2 - s/2;
	//wallRect.w = WIDTH/RES_W;
	wallRect.h = s;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &wallRect);
}
void Render::fillBg(Uint8 r, Uint8 g, Uint8 b){
	 SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	 SDL_RenderClear(renderer);
}
void Render::render(){
	SDL_RenderPresent(renderer);
}
void Render::drawPlayer(double x, double y, double dx, double dy){
	SDL_Rect plRect;
	int plX = int(x*double(GRID_SIZE)),
		plY = int(y*double(GRID_SIZE));
	plRect.x = plX -2;
	plRect.y = plY -2;
	plRect.w = 5;
	plRect.h = 5;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &plRect);
	SDL_RenderDrawLine(renderer, plX, plY, plX + int(dx), plY + int(dy));
}
void Render::drawRays(double x, double y, double dir){
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	for (int X=0; X<WIDTH; X++){
		double rayDir =  dir - fov/2 + (double(X)/double(WIDTH)) * fov;

		if (rayDir > PI*2) rayDir = rayDir - PI*2; if (rayDir < 0) rayDir = rayDir + PI*2;
		
		double distance = castRay(x, y, rayDir);
		int plX = int(x*double(GRID_SIZE)),
			plY = int(y*double(GRID_SIZE)),
			rayX = plX + cos(rayDir)*(distance*double(GRID_SIZE)),
			rayY = plY + sin(rayDir)*(distance*double(GRID_SIZE));
		SDL_RenderDrawLine(renderer, plX, plY, rayX, rayY);
	}
}
void Render::drawMap(){
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect rect;
	rect.w = GRID_SIZE;
	rect.h = GRID_SIZE;
	for (int y=0; y<MAP_W; y++)
	{
		for (int x=0; x<MAP_W; x++){
			rect.x = (rect.w*x);
			rect.y = (rect.h*y);

			
			if (map[(y*MAP_W) + x])
			{
				SDL_RenderFillRect(renderer, &rect);
			}else
			{
				SDL_RenderDrawRect(renderer, &rect);
			}
		}
	}
}