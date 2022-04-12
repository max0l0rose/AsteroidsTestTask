#pragma once

//#ifndef asteroid
//#define asteroid

//#include "MyFramework.h"

#include <cstdlib>

#include "Framework.h"
#include "Config.h"

#include <SDL_rect.h>

//enum AsterType {
//	SMALL, BIG
//};

class Asteroid
{
public:
	SDL_Point coord = {0, 0};
	SDL_Point moveVector = {0, 0};
	int collisionImmunity = 0;

	Config config;

	Asteroid()
	{
	}

	Asteroid(SDL_Point coord, SDL_Point mVector)
		: Asteroid()
	{
		this->coord = coord;
		this->moveVector = mVector;
	}

	virtual void draw() {
		drawSprite(getSprite(), coord.x, coord.y);
	}

	virtual void move() {
		if (abs(moveVector.x) >= config.speedFlag) {
			if (moveVector.x > 0) 
				coord.x += 1;
			else
				coord.x -= 1;
		}
		if (coord.x > Config::width)
			coord.x = -getWidth();
		if (coord.x < -getWidth())
			coord.x = Config::width;

		if (abs(moveVector.y) >= config.speedFlag) {
			if (moveVector.y > 0)
				coord.y += 1;
			else
				coord.y -= 1;
		}
		if (coord.y > Config::height)
			coord.y = -getHeight();
		if (coord.y < -getHeight())
			coord.y = Config::height;
	}

	virtual Sprite* getSprite() const = 0;
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;

	SDL_bool checkCollision(Asteroid* const b) {
		SDL_Rect r1;
		r1.x = coord.x;
		r1.y = coord.y;
		r1.w = getWidth();
		r1.h = getHeight();

		SDL_Rect r2;
		r2.x = b->coord.x;
		r2.y = b->coord.y;
		r2.w = b->getWidth();
		r2.h = b->getHeight();

		return SDL_HasIntersection(&r1, &r2);
	}

	~Asteroid() 
	{
	}

protected:
};



//#endif