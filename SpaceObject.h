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
	SDL_Point vector = { 0 };

	SpaceObject(Config& cfg) : config(cfg)
	{
	}

	SpaceObject(SDL_Point coord, SDL_Point vector, Config& cfg)
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

	virtual Sprite* getSprite() const = 0;
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;

};

