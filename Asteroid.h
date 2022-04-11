#pragma once

//#ifndef asteroid
//#define asteroid

//#include "MyFramework.h"

#include "Framework.h"
#include "Config.h"

#include <SDL_rect.h>

//enum AsterType {
//	SMALL, BIG
//};

class Asteroid
{
public:
	SDL_FPoint coord = {0, 0};
	SDL_FPoint moveVector = {0, 0};

	Asteroid() {
	}

	virtual void draw() {
		drawSprite(getSprite(), coord.x, coord.y);
	}

	virtual void move() {
		coord.x += moveVector.x;
		if (coord.x > Config::width)
			coord.x = -getWidth();
		coord.y += moveVector.y;
		if (coord.y > Config::height)
			coord.y = -getHeight();
	}

	virtual Sprite* getSprite() = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;

protected:
};



//#endif