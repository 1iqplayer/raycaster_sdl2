#include <SDL2/SDL.h>
#include <renderer.h>
#include <common.h>
#include <stdio.h>>
#include <math.h>

iVec getTexSize(SDL_Texture* tex)
{
	iVec size;
	SDL_Point s;
	SDL_QueryTexture(tex, NULL, NULL, &s.x, &s.y);
	size.x = s.x; size.y = s.y;
	return size;
}
ray castRay(double x, double y, double dir){
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
	// Walking
	double maxDistance = 100.0;
	double distance = 0.0;
	bool hit = false;
	bool vertical;

	while (!hit and distance < maxDistance)
	{
		if (rayLen.x < rayLen.y)
		{
			vertical = true;
			mapCheck.x += step.x;
			distance = rayLen.x;
			rayLen.x += scale.x;
		}
		else
		{
			vertical = false;
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

	// Endpoint vector
	ray temp;
	temp.vertical = vertical;
	temp.dist = distance;
	return temp;
}
Render::Render(SDL_Window *w){
	renderer = SDL_CreateRenderer(w, -1, 0);
	texture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("brick.bmp"));
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void Render::drawWall(double x, double y, double dir){
	for(int X=0; X<WIDTH; X++)
	{
		// Calculating ray direction respectively to field of view
		double rayDir =  dir - fov/2 + (double(X)/double(WIDTH)) * fov;
		// Calculating difference between dir and raydir to avoid fisheye effect
		double diff = dir - rayDir;
		// Normalizing angle to max 2Pi
		if (diff > PI*2) diff = diff - PI*2; if (diff < 0) diff = diff + PI*2;
		
		// Camera ray length
		ray cast = castRay(x, y, rayDir);
		double dist = cast.dist;
		double maxDist = 15.0;
		// Point where ray hit
		double 	rayX = x + cos(rayDir)*dist,
				rayY = y + sin(rayDir)*dist,
				onWall;
		if (!cast.vertical)
			onWall = rayX - (long)rayX;
		else
			onWall = rayY - (long)rayY;
		// Removing fisheye effect
		dist = dist * cos(diff);
		if (X == WIDTH/2)
		printf(cast.vertical ? "true\n" : "false\n");

		// DRAW
		if (dist <= maxDist)
		{
			// Height of wall
			int wallH = (GRID_SIZE*HEIGHT)/(dist*GRID_SIZE);
			// Line coordinates
			iVec pos0, pos1;
			pos0.x = X;
			pos0.y = HEIGHT/2 - wallH/2;
			pos1.x = X;
			pos1.y = HEIGHT/2 + wallH/2;
			
			// Draw texture
			iVec size = getTexSize(texture);
			SDL_Rect src, dst;
			src.x = double(size.x) * onWall;
			src.y = 0;
			src.w = 1;
			src.h = size.y;

			dst.x = X;
			dst.y = pos0.y;
			dst.w = 1;
			dst.h = wallH;
			SDL_RenderCopy(renderer, texture, &src, &dst);

			// Color depth
			int color =fmax(0, fmin(255.0, (dist/8.0) * 255));
			// Draw shade
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, color);
			SDL_RenderDrawLine(renderer, pos0.x, pos0.y, pos1.x, pos1.y);
		}
		
	}
}
void Render::fillBg(Uint8 r, Uint8 g, Uint8 b){
	 SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	 SDL_RenderClear(renderer);
	 // Fill gradient
	 for(int y=0; y<HEIGHT/2; y++)
	 {
	 int color =(double(y)/(double(HEIGHT)/2))* 100.0;
	 printf("color:%i\n", color);
	 SDL_SetRenderDrawColor(renderer, color, color, color, 255);
	 SDL_RenderDrawLine(renderer, 0, HEIGHT/2+y, WIDTH, HEIGHT/2+y);
	}
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

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
	SDL_RenderFillRect(renderer, &plRect);
	SDL_RenderDrawLine(renderer, plX, plY, plX + int(dx), plY + int(dy));
}
void Render::drawRays(double x, double y, double dir){
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 90);
	for (int X=0; X<WIDTH; X++){
		double rayDir =  dir - fov/2 + (double(X)/double(WIDTH)) * fov;

		if (rayDir > PI*2) rayDir = rayDir - PI*2; if (rayDir < 0) rayDir = rayDir + PI*2;
		
		double distance = castRay(x, y, rayDir).dist;
		int plX = int(x*double(GRID_SIZE)),
			plY = int(y*double(GRID_SIZE)),
			rayX = plX + cos(rayDir)*(distance*double(GRID_SIZE)),
			rayY = plY + sin(rayDir)*(distance*double(GRID_SIZE));
		SDL_RenderDrawLine(renderer, plX, plY, rayX, rayY);
	}
}
void Render::drawMap(){
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);

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