#pragma once
#include <SDL_rect.h>

#include "FrameworkAPI.h"

#include "Config.h"

class SpaceObject
{
protected:
	//static Sprite* sprite;

	virtual Sprite* getSprite() const = 0;
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;

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
		drawSprite(getSprite(), coord.x + config.position.x, coord.y + config.position.y);
	}

};

