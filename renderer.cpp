#include <SDL2/SDL.h>
#include <renderer.h>
#include <common.h>
#include <stdio.h>>
#include <math.h>

Render::Render(SDL_Window *w){
	printf("Renderer initialized!");
	renderer = SDL_CreateRenderer(w, -1, 0);
}

void Render::drawWall(int x, int s){
	SDL_Rect wallRect;
	wallRect.x = x * (WIDTH/RES_W);
	wallRect.y = HEIGHT/2 - s/2;
	wallRect.w = WIDTH/RES_W;
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
void Render::drawPlayer(float x, float y, double dx, double dy){
	SDL_Rect plRect;
	plRect.x = x -2;
	plRect.y = y -2;
	plRect.w = 5;
	plRect.h = 5;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &plRect);
	SDL_RenderDrawLine(renderer, int(x), int(y), int(x) + int(dx), int(y) + int(dy));
}
void Render::drawRays(int x, int y, double dir){
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	for (int X=0; X<WIDTH; X++){
		double rayDir = double(X)/double(WIDTH) * fov + dir - (fov/2);

		if (rayDir > PI*2) rayDir = rayDir - PI*2; if (rayDir < 0) rayDir = rayDir + PI*2;
		double rayDX = double(x) + cos(rayDir) * 500;
		double rayDY = double(y) + sin(rayDir) * 500;
		SDL_RenderDrawLine(renderer, x, y, int(rayDX), int(rayDY));
	}
}
void Render::drawMap(){
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect rect;
	rect.w = 40;
	rect.h = 40;
	for (int y=0; y<MAP_H; y++)
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