#include<SDL.h>

bool quit = false;
SDL_Event event;
int ballx = 10;
int bally = 10;
int ballvelx = 1;
int ballvely = 1;

int bkw = 800;
int bkh = 600;
int bkwmin = 0;
int bkhmin = 0;

void EventHandler() {

	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		quit = true;
	}

}

void moveBall() {
		ballx = ballx + ballvelx;
		bally = bally + ballvely;
}



int main(int argc, char ** argv) {

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow("MOJA GRA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,800,600,0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,0);
	
	SDL_Rect bkrect = { 0,0,800,600 };
	SDL_Surface *ball = SDL_LoadBMP("ball.bmp");
	SDL_Surface *bk = SDL_LoadBMP("bk.bmp");
	SDL_Texture *balltexture = SDL_CreateTextureFromSurface(renderer, ball);
	SDL_Texture *bktexture = SDL_CreateTextureFromSurface(renderer, bk);
	SDL_RenderCopy(renderer, bktexture, NULL, &bkrect);
	

	while (!quit) {
		EventHandler();
		SDL_Rect ballrect = { ballx,bally,20,30 };
		moveBall();
		SDL_RenderCopy(renderer, bktexture, NULL, &bkrect);
		SDL_RenderCopy(renderer, balltexture, NULL, &ballrect);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}


	SDL_Quit();
	return 0;


}