#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <stdlib.h>
#include "Physics.h"
#include "Game.h"

Game::Game() {
	start();
}

Game::~Game() {

}

void Game::InitializeBrick() {
	brickrect[0][0] = { 50,50,brickw,brickh };
	brickrect[0][1] = { 150,50,brickw,brickh };
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

void Game::EventHandler() {

	SDL_PollEvent(&sdlEvent);
	if (sdlEvent.type == SDL_QUIT) {
		quit = true;
	}

	else if (sdlEvent.type == SDL_JOYAXISMOTION)
	{
		if (sdlEvent.jaxis.which == 0)
		{
			if (sdlEvent.jaxis.axis == 0)
			{
				//std::cout << "axis=" << sdlEvent.jaxis.value << std::endl;
				if (sdlEvent.jaxis.value < -8000 && cartx > 0)
					//cartx = cartx - 2;
				{
					cartPhysics.velocity[0] = cartPhysics.velocity[0] > 0.0 ? 0.0 : cartPhysics.velocity[0];
					cartPhysics.velocity[0] -= 0.001;
					//cartPhysics.velocity[0] += sdlEvent.jaxis.value / (4000000.0 * 2.67);

				}
				else if (sdlEvent.jaxis.value > 8000 && cartx < bkw - 60)
					//cartx = cartx + 2;
				{
					cartPhysics.velocity[0] = cartPhysics.velocity[0] < 0.0 ? 0.0 : cartPhysics.velocity[0];
					cartPhysics.velocity[0] += 0.001;
					//cartPhysics.velocity[0] += sdlEvent.jaxis.value / (4000000.0 * 2.67);
				}
					}
		}
	}
	else if (sdlEvent.type == SDL_KEYDOWN) {
		if (sdlEvent.key.keysym.sym == SDLK_LEFT && cartx > 0) {
			//cartx = cartx - 2;
			cartPhysics.velocity[0] = cartPhysics.velocity[0] > 0.0 ? 0.0 : cartPhysics.velocity[0];
			cartPhysics.velocity[0] -= 0.001;
		}
		if (sdlEvent.key.keysym.sym == SDLK_RIGHT && cartx < bkw - 60) {
			//cartx = cartx + 2;
			cartPhysics.velocity[0] = cartPhysics.velocity[0] < 0.0 ? 0.0 : cartPhysics.velocity[0];
			cartPhysics.velocity[0] += 0.001;
		}

	}
	/*
	else if (sdlEvent.type == SDL_KEYUP) {
		if (sdlEvent.key.keysym.sym == SDLK_LEFT || sdlEvent.key.keysym.sym == SDLK_RIGHT) {
			cartPhysics.velocity[0] = 0.0;
		}
	}
	*/
}
void Game::gameOver() {
	SDL_Surface *go = SDL_LoadBMP("img/gameover.bmp");
	SDL_Texture *gotexture = SDL_CreateTextureFromSurface(renderer, go);
	SDL_Rect gorect = { 0,0,bkw,bkh };
	SDL_RenderCopy(renderer, gotexture, NULL, &gorect);
	SDL_RenderPresent(renderer);
	SDL_Delay(3000);

}

void Game::moveBall(int dt) {
	ballx = ballx + ballvelx;
	bally = bally + ballvely;
	ball_physics.move(dt, true);
	ballx = (int)ball_physics.position[0];
	bally = (int)ball_physics.position[1];

	cartPhysics.move(dt, false);

	if (cartx < 0)
		cartPhysics.position[0] = 0.0;
	if (cartx > bkw - 60)
		cartPhysics.position[0] = bkw - 60;
	cartx = (int)cartPhysics.position[0];
}

void Game::ball_collision() {
	if (ballx < bkwmin) {
		ball_physics.bounce(0, 1.0);
	}
	else if (ballx > bkw - 30) {
		ball_physics.bounce(0, -1.0);
	}

	if (bally < bkhmin) {
		ball_physics.bounce(1, 1.0);
	}
	//else if(bally > bkh - 30) {
	//ball_physics.bounce(1, -1.0);
	//}
	if (bally > bkh + 60) {
		gameOver();
		quit = true;
		//ball_physics.bounce(1, -1.0);
	}
	int ballscaling = 20;
	if (bally + ballscaling >= carty && bally + ballscaling <= carty + 30 && ballx + ballscaling >= cartx && ballx + ballscaling <= cartx + 60) {
		ball_physics.bounce(1, -1.0);
	}
}

bool Game::ball_brick_collision_detect(SDL_Rect rect1, SDL_Rect rect2) {
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
void Game::ball_brick_collision() {
	bool a;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			a = ball_brick_collision_detect(brickrect[i][j], ballrect);//pozycja cegly i pilki
			if (a == true) {
				brickrect[i][j].x = 30000;
				ball_physics.bounce(1, 1.0);
				delete_brick_count++;
			}

			a = false;
		}
	}
}
void Game::Destroy() {
	SDL_FreeSurface(brick);
	SDL_FreeSurface(bk);
	SDL_FreeSurface(cart);
	SDL_FreeSurface(ball);
	SDL_DestroyTexture(carttexture);
	SDL_DestroyTexture(bricktexture);
	SDL_DestroyTexture(bktexture);
	SDL_DestroyTexture(balltexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

}
void Game::winning() {
	SDL_Surface *win = SDL_LoadBMP("img/win.bmp");
	SDL_Texture *wintexture = SDL_CreateTextureFromSurface(renderer, win);
	SDL_Rect winrect = { 250,200,350,350 };
	SDL_RenderCopy(renderer, wintexture, NULL, &winrect);
	SDL_RenderPresent(renderer);
	SDL_Delay(3000);

}

void Game::start() {

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK);

	//SDL_Joystick *joystick = SDL_JoystickOpen(0);


	//std::cout << "controller name: " << SDL_JoystickName(joystick) << std::endl;
	//std::cout << "Num Axes: " << SDL_JoystickNumAxes(joystick) << std::endl;
	//std::cout << "Num Buttons: " << SDL_JoystickNumButtons(joystick) << std::endl;

	window = SDL_CreateWindow("Brick breaker in space", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "Error: " << Mix_GetError() << std::endl;
	}
	Mix_Music *music = Mix_LoadMUS("./music.wav");

	Mix_PlayMusic(music, -1);

	SDL_Rect bkrect = { 0,0,800,600 };
	InitializeBrick();

	ball = SDL_LoadBMP("img/01.bmp");
	bk = SDL_LoadBMP("img/bk.bmp");
	cart = SDL_LoadBMP("img/r.bmp");
	brick = SDL_LoadBMP("img/brick.bmp");
	balltexture = SDL_CreateTextureFromSurface(renderer, ball);
	bktexture = SDL_CreateTextureFromSurface(renderer, bk);
	carttexture = SDL_CreateTextureFromSurface(renderer, cart);
	bricktexture = SDL_CreateTextureFromSurface(renderer, brick);

	SDL_RenderCopy(renderer, bktexture, NULL, &bkrect);



	int now;
	int frameLenght = 0;
	while (!quit) {
		now = SDL_GetTicks();
		EventHandler();
		ballrect = { ballx,bally,20,30 };
		SDL_Rect cartrect = { cartx,carty,60,30 };
		moveBall(frameLenght);
		ball_collision();
		ball_brick_collision();
		if (delete_brick_count == no_of_bricks) {
			winning();
			quit = true;

		}

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
		frameLenght = SDL_GetTicks() - now; //
		//std::cout << "cartx: " << cartx << " carty" << carty << std::endl;
		//std::cout << "cartx: " << ball_physics.velocity[0] << " vely: " << ball_physics.velocity[1] << std::endl;
	}
	Mix_FreeMusic(music);
	
	Mix_Quit();
	
	Destroy();
	
	SDL_Quit();
	
}