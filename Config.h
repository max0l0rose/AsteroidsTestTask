#pragma once

#include "SDL.h"
//#include "Player.h"

struct Config
{
	int width = 0, height = 0;
	int speedFlag = 0;
	SDL_Point position = { 0 };


	void setPause(bool pause) {
		Config::pause = pause;
	}
	bool getPause() {
		return Config::pause;
	}

private:
	bool pause = false;
};

