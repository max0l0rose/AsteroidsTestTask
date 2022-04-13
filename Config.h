#pragma once

#include "SDL.h"
//#include "Player.h"

struct Config
{
	static int width, height;
	static int speedFlag;

	static void setPause(bool pause) {
		Config::pause = pause;
	}
	static bool getPause() {
		return Config::pause;
	}

private:
	static bool pause;
};

