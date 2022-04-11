#include <SDL2/SDL.h>
#include <stdio.h>
#include <rederer.h>
#include <common.h>

using namespace std;

int screen_width = 800, 
	screen_height = 500;

SDL_Window* window = NULL;
SDL_Surface* screenSurf = NULL;
SDL_Surface* imgSurf = NULL;
Render rend;

bool init(){
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return false;

	// Create Window
	window = SDL_CreateWindow(
		"Raycaster", 
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 
		screen_width, 
		screen_height, 
		SDL_WINDOW_SHOWN);
	if (window == NULL)
		return false;

	screenSurf = SDL_GetWindowSurface(window);
	rend = Render();
	return true;
}

void close(){
	// Deallocate surfaces
	SDL_FreeSurface(imgSurf);
	imgSurf = NULL;

	// Destory window
	SDL_DestroyWindow(window);
	window = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

void loadMedia(const char* path){

	imgSurf = SDL_LoadBMP(path);
	if (imgSurf == NULL){
		printf("Problem with loading media: %s\n", SDL_GetError());
	}
}

int main(int argc, char* argv[]){
	if (!init()){
		printf("Problem with initialization: %s\n", SDL_GetError());
		return -1;
	}

	loadMedia("test.bmp");
	SDL_FillRect( screenSurf, NULL, SDL_MapRGB( screenSurf->format, 0xff, 0xff, 0xff ) );
	
	bool running = true;
	while(running){
		SDL_Event ev;

		while( SDL_PollEvent(&ev) != 0 ){
			if(ev.type == SDL_QUIT)
				running = false;
		}
		SDL_UpdateWindowSurface(window);	
	}
	
	close();
	return 1;
}