#include<SDL.h>
#include <iostream>
#include <stdlib.h>
#include "Physics.h"

bool quit = false;
SDL_Event event;

int ballvelx = 1;
int ballvely = 1;


int bkw = 800;
int bkh = 600;
int ballx = bkw / 2;
int bally = bkh - 40;
int brickw = 80;
int brickh = 35;
int bkwmin = 0;
int bkhmin = 0;
int cartx = bkw / 2;
int carty = bkh-30;
Physics ball_physics = Physics({ ballx / 1.0, bally / 1.0 }, { ballvelx / 1.0, ballvely / 1.0 }, { 0.000798, 0.000798 }); //pozycja x,y predkosc, x,y , przyspieszenie xy
SDL_Surface *brick;
SDL_Texture *bricktexture;
SDL_Rect brickrect[3][7];
SDL_Rect ballrect;


void InitializeBrick() {
	brickrect[0][0] = { 50,50,brickw,brickh };
	brickrect[0][1] = {	150,50,brickw,brickh };
	brickrect[0][2] = { 250,50,brickw,brickh };
	brickrect[0][3] = { 350,50,brickw,brickh };
	brickrect[0][4] = { 450,50,brickw,brickh };
	brickrect[0][5] = { 550,50,brickw,brickh };
	brickrect[0][6] = { 650,50,brickw,brickh };
	brickrect[1][0] = { 50,100,brickw,brickh };
	brickrect[1][1] = { 150,100,brickw,brickh };
	brickrect[1][2] = { 250,100,brickw,brickh };
	brickrect[1][3] = { 350,100,brickw,brickh };
	brickrect[1][4] = { 450,100,brickw,brickh };
	brickrect[1][5] = { 550,100,brickw,brickh };
	brickrect[1][6] = { 650,100,brickw,brickh };
	brickrect[2][0] = { 50,150,brickw,brickh };
	brickrect[2][1] = { 150,150,brickw,brickh };
	brickrect[2][2] = { 250,150,brickw,brickh };
	brickrect[2][3] = { 350,150,brickw,brickh };
	brickrect[2][4] = { 450,150,brickw,brickh };
	brickrect[2][5] = { 550,150,brickw,brickh };
	brickrect[2][6] = { 650,150,brickw,brickh };



}

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

void moveBall(int dt) {
		ballx = ballx + ballvelx;
		bally = bally + ballvely;
		ball_physics.move(dt, true);
		ballx = (int)ball_physics.position[0];
		bally = (int)ball_physics.position[1];
}

void ball_collision() {
	if (ballx < bkwmin) {
		ball_physics.bounce(0, 1.0);
	}
	else if (ballx > bkw - 30) {
		ball_physics.bounce(0, -1.0); 
	}

	if (bally < bkhmin) {
		ball_physics.bounce(1, 1.0);
	}
	else if(bally > bkh - 30) {
		ball_physics.bounce(1, -1.0);
	}
	int ballscaling = 20;
	if (bally + ballscaling >= carty && bally + ballscaling <= carty + 30 && ballx + ballscaling >= cartx && ballx + ballscaling <= cartx + 60) {
		ball_physics.bounce(1, -1.0);
	}
}

bool ball_brick_collision_detect(SDL_Rect rect1, SDL_Rect rect2) { 
	if (rect1.x > rect2.x + rect2.w) {
		return false;
	}
	if (rect1.x + rect1.w < rect2.x) {
		return false;
	}
	if (rect1.y > rect2.y + rect2.h) {
		return false;
	}
	if (rect1.y + rect1.h < rect2.y) {
		return false;
	}
	return true;
}
void ball_brick_collision() {
	bool a,b;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			a = ball_brick_collision_detect(brickrect[i][j], ballrect);//pozycja cegly i pilki
			if (a == true) {
				brickrect[i][j].x = 30000;
				ball_physics.bounce(1, 1.0);
				}
						
			a = false;
		}
	}
}

int main(int argc, char ** argv) {

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow("MOJA GRA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,800,600,0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,0);
	
	SDL_Rect bkrect = { 0,0,800,600 };
	InitializeBrick();
	
	SDL_Surface *ball = SDL_LoadBMP("ball.bmp");
	SDL_Surface *bk = SDL_LoadBMP("bk.bmp");
	SDL_Surface *cart = SDL_LoadBMP("cart.bmp");
	SDL_Surface *brick = SDL_LoadBMP("brick.bmp");
	SDL_Texture *balltexture = SDL_CreateTextureFromSurface(renderer, ball);
	SDL_Texture *bktexture = SDL_CreateTextureFromSurface(renderer, bk);
	SDL_Texture *carttexture = SDL_CreateTextureFromSurface(renderer, cart);
	SDL_Texture *bricktexture = SDL_CreateTextureFromSurface(renderer, brick);

	SDL_RenderCopy(renderer, bktexture, NULL, &bkrect);

	

	int frame_time = 3;
	int now;
	int sleep_time = 0;
	while (!quit) {
		now = SDL_GetTicks();
		EventHandler();
		ballrect = { ballx,bally,20,30 };
		SDL_Rect cartrect = { cartx,carty,60,30 };
		moveBall(sleep_time);
		ball_collision();
		ball_brick_collision();
		SDL_RenderCopy(renderer, bktexture, NULL, &bkrect);
		SDL_RenderCopy(renderer, balltexture, NULL, &ballrect);
		SDL_RenderCopy(renderer, carttexture, NULL, &cartrect);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[0][0]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[0][1]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[0][2]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[0][3]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[0][4]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[0][5]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[0][6]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[1][0]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[1][1]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[1][2]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[1][3]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[1][4]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[1][5]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[1][6]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[2][0]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[2][1]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[2][2]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[2][3]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[2][4]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[2][5]);
		SDL_RenderCopy(renderer, bricktexture, NULL, &brickrect[2][6]);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		sleep_time = SDL_GetTicks() - now;
		//std::cout << "cartx: " << cartx << " carty" << carty << std::endl;
		//std::cout << "cartx: " << ball_physics.velocity[0] << " vely: " << ball_physics.velocity[1] << std::endl;
	}


	SDL_Quit();
	return 0;


}