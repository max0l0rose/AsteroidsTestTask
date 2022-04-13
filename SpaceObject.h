#pragma once
#include <SDL_rect.h>

#include "FrameworkAPI.h"

class SpaceObject
{
protected:
	//static Sprite* sprite;

	virtual Sprite* getSprite() const = 0;
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;

public:
	SDL_Point coord = { 0 };
	SDL_Point vector = { 0 };

	SpaceObject()
	{
	}

	SpaceObject(SDL_Point coord, SDL_Point vector)
	{
		this->coord = coord;
		this->vector = vector;
	}

	virtual void draw() {
		drawSprite(getSprite(), coord.x, coord.y);
	}

};

