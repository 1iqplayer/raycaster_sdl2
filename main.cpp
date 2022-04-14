#include <SDL2/SDL.h>
#include <stdio.h>
#include <renderer.h>
#include <common.h>
#include <player.h>

using namespace std;
SDL_Window* window = NULL;

bool init(){
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return false;

	// Create Window
	window = SDL_CreateWindow(
		"Raycaster", 
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 
		WIDTH, 
		HEIGHT, 
		SDL_WINDOW_SHOWN);

	return true;
}

void close(SDL_Window* w){
	// Deallocate surfaces

	// Destory window
	SDL_DestroyWindow(w);

	// Quit SDL subsystems
	SDL_Quit();
}


int main(int argc, char* argv[]){
	if (!init()){
		printf("Problem with initialization: %s\n", SDL_GetError());
		return 1;
	}
	Render rend = Render(window);

	// Game related
	Player player = Player();
	player.x = 2;
	player.y = 2;
	long int currTime = SDL_GetTicks();
	long int lastTime = currTime;

	
	// Main loop and event handling
	bool running = true;
	while(running){
		SDL_Event ev;
		currTime = SDL_GetTicks();

		if (currTime - lastTime >= fps){
		lastTime = currTime;

		// Handle events
		while( SDL_PollEvent(&ev) != 0 ){
			if(ev.type == SDL_QUIT)
				running = false;
			if(ev.type == SDL_KEYDOWN){
				switch (ev.key.keysym.sym)
				{
				case SDLK_a: player.changeDir(-0.1); break;
                case SDLK_d: player.changeDir(0.1); break;
                case SDLK_w: player.move(.1); break;
                case SDLK_s: player.move(-.1); break;
				}
			}
		}
		// Draw things
		rend.fillBg(150, 150, 150);
		rend.drawMap();
		rend.drawRays(player.x, player.y, player.dir);
		rend.drawPlayer(player.x, player.y, player.dx, player.dy);
		rend.render();	
	}
	}
	
	close(window);
	return 0;
}