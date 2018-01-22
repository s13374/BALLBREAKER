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
int cartx = bkw / 2;
int carty = bkh-30;

void EventHandler() {

	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		quit = true;
	}
	else if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_LEFT && cartx > 0) {
			cartx = cartx - 2;
		}
		if (event.key.keysym.sym == SDLK_RIGHT && cartx < bkw - 60) {
			cartx = cartx + 2;
		}
	}
}

void moveBall() {
		ballx = ballx + ballvelx;
		bally = bally + ballvely;
}

void ball_collision() {
	if (ballx < bkwmin || ballx > bkw - 30) {
		ballvelx = -ballvelx;
	}
	if (bally < bkhmin || bally >bkh - 30) {
		ballvely = -ballvely;
	}
	int ballscaling = 20;
	if (bally + ballscaling >= carty && bally + ballscaling <= carty + 30 && ballx + ballscaling >= cartx && ballx + ballscaling <= cartx + 60) {
		ballvely = -ballvely;
	}
}

int main(int argc, char ** argv) {

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow("MOJA GRA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,800,600,0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,0);
	
	SDL_Rect bkrect = { 0,0,800,600 };
	
	SDL_Surface *ball = SDL_LoadBMP("ball.bmp");
	SDL_Surface *bk = SDL_LoadBMP("bk.bmp");
	SDL_Surface *cart = SDL_LoadBMP("cart.bmp");
	SDL_Texture *balltexture = SDL_CreateTextureFromSurface(renderer, ball);
	SDL_Texture *bktexture = SDL_CreateTextureFromSurface(renderer, bk);
	SDL_Texture *carttexture = SDL_CreateTextureFromSurface(renderer, cart);

	SDL_RenderCopy(renderer, bktexture, NULL, &bkrect);
	

	while (!quit) {
		EventHandler();
		SDL_Rect ballrect = { ballx,bally,20,30 };
		SDL_Rect cartrect = { cartx,carty,60,30 };
		moveBall();
		ball_collision();
		SDL_RenderCopy(renderer, bktexture, NULL, &bkrect);
		SDL_RenderCopy(renderer, balltexture, NULL, &ballrect);
		SDL_RenderCopy(renderer, carttexture, NULL, &cartrect);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}


	SDL_Quit();
	return 0;


}