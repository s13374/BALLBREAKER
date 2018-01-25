#pragma once
#include "Physics.h"
#include <SDL.h>

class Game {
private:
	bool quit = false;
	SDL_Event sdlEvent;


	SDL_Surface *brick;
	SDL_Surface *ball;
	SDL_Surface *bk;
	SDL_Surface *cart;

	SDL_Texture *bricktexture;
	SDL_Texture *balltexture;
	SDL_Texture *bktexture;
	SDL_Texture *carttexture;

	SDL_Rect brickrect[3][7];
	SDL_Rect ballrect;

	SDL_Window *window;
	SDL_Renderer *renderer;

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
	int carty = bkh - 30;
	int delete_brick_count = 0;
	int no_of_bricks = 21;
	Physics ball_physics = Physics({ ballx / 1.0, bally / 1.0 }, { ballvelx / 3.0, ballvely / 3.0 }, { 0.0000798, 0.00000798 }); //pozycja x,y predkosc, x,y , przyspieszenie xy
	Physics cartPhysics = Physics({ cartx / 1.0, carty / 1.0 }, { 0.0 }, { 0.0, 0.0});

	void Destroy();
	void InitializeBrick();
	void EventHandler();
	void gameOver();
	void moveBall(int dt);
	void ball_collision();
	bool ball_brick_collision_detect(SDL_Rect rect1, SDL_Rect rect2);
	void ball_brick_collision();
	void winning();

public:
	void start();
	Game();
	~Game();
};
