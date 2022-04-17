#pragma once
#include <SDL_rect.h>

#include "FrameworkAPI.h"
#include "Config.h"

#include <cmath>

class SpaceObject
{
protected:
	Config& config;

public:
	SDL_FPoint coord = { 0 };
	SDL_FPoint vect = { 0 };
	int collisionFlag = 0;

	SpaceObject(Config& cfg) : config(cfg)
	{
	}

	SpaceObject(SDL_FPoint& coord, SDL_FPoint& vect, Config& cfg) : config(cfg)
	{
		this->coord = coord;
		this->vect = vect;
	}


	virtual void draw() {
		int x = coord.x - config.position.x;
		int y = coord.y - config.position.y;
		drawSprite(getSprite(), x, y);
	}


	virtual bool move()  // return false - if it is needed to delete 
	{
		if (coord.x > config.position.x + config.width)
			coord.x = config.position.x - getWidth();
		if (coord.x < config.position.x - getWidth())
			coord.x = config.position.x + config.width;

		if (coord.y > config.position.y + config.height)
			coord.y = config.position.y - getHeight();
		if (coord.y < config.position.y - getHeight())
			coord.y = config.position.y + config.height;

		coord.x += vect.x;
		coord.y += vect.y;

		return true;
	}


	virtual SDL_bool checkCollision(const SpaceObject& b) {
		SDL_Rect r1;
		r1.x = coord.x;
		r1.y = coord.y;
		r1.w = getWidth();
		r1.h = getHeight();

		SDL_Rect r2;
		r2.x = b.coord.x;
		r2.y = b.coord.y;
		r2.w = b.getWidth();
		r2.h = b.getHeight();

		SDL_Rect ri; //stub
		SDL_bool res = SDL_IntersectRect(&r1, &r2, &ri);

		return res;
	}

	virtual Sprite* getSprite() const = 0;
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;
};

