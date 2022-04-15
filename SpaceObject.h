#pragma once
#include <SDL_rect.h>

#include "FrameworkAPI.h"
#include "Config.h"

class SpaceObject
{
protected:
	Config& config;

public:
	SDL_Point coord = { 0 };
	SDL_FPoint vector = { 0 };

	SpaceObject(Config& cfg) : config(cfg)
	{
	}

	SpaceObject(SDL_Point coord, SDL_FPoint vector, Config& cfg)
		: config(cfg)
	{
		this->coord = coord;
		this->vector = vector;
	}

	virtual void draw() {
		int x = coord.x - config.position.x;
		int y = coord.y - config.position.y;
		drawSprite(getSprite(), x, y);
	}

	virtual SDL_bool checkCollision(SpaceObject& b) {
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

