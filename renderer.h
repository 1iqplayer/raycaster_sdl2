#include <SDL2/SDL.h>
#include <common.h>>
class Render{
	SDL_Renderer* renderer = NULL;
public:
	Render(SDL_Window *w);

	void drawWall(int x, int s);
	void render();
	void fillBg(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0);
	void drawMap();
	void drawPlayer(double x, double y, double dx, double dy);
	void drawRays(double x, double y, double dir);
};