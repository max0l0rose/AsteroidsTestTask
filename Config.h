#pragma once

#include "SDL.h"
//#include "Player.h"

struct Config
{
	int width = 0, height = 0;
	int speedFlag = 0;
	SDL_Point position = { 0 };

#define GAME_STOPPED 0
#define GAME_WIN 1
#define GAME_INIT 2
#define GAME_GOES 3

	int gameMode = GAME_STOPPED;

	void setPause(bool pause) {
		pause = pause;
	}
	bool getPause() {
		return pause;
	}

private:
	bool pause = false;
};

