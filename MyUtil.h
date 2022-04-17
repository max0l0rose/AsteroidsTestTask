#pragma once

#include <stdlib.h>

#include "SDL.h"

class MyUtil
{
public:
	static void getRndVector(SDL_FPoint& vect) {
		vect.x = rand() % 600 - 300;
		vect.x /= 200;
		vect.y = rand() % 600 - 300;
		vect.y /= 200;
	}

	static void movePointRnd(SDL_FPoint& point, int w, int h) {
		point.x += rand() % w*2 - w;
		point.y += rand() % h*2 - h;
	}

};

