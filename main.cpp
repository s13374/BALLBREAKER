#include<SDL.h>
int main(int argc, char ** argv) {

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow("MOJA GRA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,640,480,0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,0);
	SDL_Rect ballrect = { 20,30,20,30 };
	SDL_Surface *ball = SDL_LoadBMP("ball.bmp");
	SDL_Texture *balltexture = SDL_CreateTextureFromSurface(renderer, ball);


	SDL_Delay(5000);
	SDL_Quit();
	return 0;


}