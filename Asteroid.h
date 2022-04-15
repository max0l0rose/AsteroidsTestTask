#pragma once
//#ifndef asteroid
//#define asteroid

#include <cstdlib>
#include <SDL_rect.h>

//#include "Framework.h"
#include "Config.h"
#include "SpaceObject.h"


class Asteroid : public SpaceObject
{
public:
	Asteroid(Config& cfg) 
		: SpaceObject(cfg)
	{
	}

	Asteroid(SDL_FPoint coord, SDL_FPoint vector, Config& cfg)
		: SpaceObject(coord, vector, cfg)
	{
	}

	virtual void move() {
		if (abs(vector.x) >= config.speedFlag) {
			if (vector.x > 0.001) 
				coord.x += 1;
			else
				coord.x -= 1;
		}
		if (coord.x > config.position.x+config.width)
			coord.x = config.position.x-getWidth();
		if (coord.x < config.position.x-getWidth())
			coord.x = config.position.x+config.width;

		if (abs(vector.y) >= config.speedFlag) {
			if (vector.y > 0.001)
				coord.y += 1;
			else
				coord.y -= 1;
		}
		if (coord.y > config.position.y+config.height)
			coord.y = config.position.y-getHeight();
		if (coord.y < config.position.y-getHeight())
			coord.y = config.position.y+config.height;
	}

	~Asteroid() 
	{
	}

protected:
};



//#endif