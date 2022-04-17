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
	bool showMap = false,
		 showPlayer = false;
	bool move[] = {false, false, false, false, false, false};

	
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
			if(ev.type == SDL_KEYDOWN or ev.type == SDL_KEYUP){
				const Uint8 *keys = SDL_GetKeyboardState(NULL);
				if (keys[SDL_SCANCODE_A])
					move[3] = true; else move[3] = false; 
				if (keys[SDL_SCANCODE_S])
					move[2] = true; else move[2] = false;
				if (keys[SDL_SCANCODE_D])
					move[1] = true; else move[1] = false;
				if (keys[SDL_SCANCODE_W])
					move[0] = true; else move[0] = false;
				if (keys[SDL_SCANCODE_RIGHT])
					move[4] = true; else move[4] = false;
				if (keys[SDL_SCANCODE_LEFT])
					move[5] = true; else move[5] = false;
				if(ev.type == SDL_KEYDOWN){
					if (ev.key.keysym.sym == SDLK_o)
						showMap = !showMap;
					if (ev.key.keysym.sym == SDLK_p)
						showPlayer = !showPlayer;
				}				
			}
		}
		// Move player
		if (move[0])
			player.move(.12);
		if (move[1])
			player.move(.12, 1);
		if (move[2])
			player.move(.12, 2);
		if (move[3])
			player.move(.12, 3);
		if (move[4])
			player.changeDir(.1);
		if (move[5])
			player.changeDir(-.1);
		// Draw things
		rend.fillBg(150, 150, 150);
		rend.drawWall(player.x, player.y, player.dir);
		if (showMap)
			rend.drawMap();
		if (showPlayer)
		{
			rend.drawRays(player.x, player.y, player.dir);
			rend.drawPlayer(player.x, player.y, player.dx, player.dy);
		}
		rend.render();	
	}
	}
	
	close(window);
	return 0;
}