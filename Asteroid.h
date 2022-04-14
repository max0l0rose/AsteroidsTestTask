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
	int collisionFlag = 0;

	Asteroid(Config& cfg) 
		: SpaceObject(cfg)
	{
	}

	Asteroid(SDL_Point coord, SDL_Point vector, Config& cfg)
		: SpaceObject(coord, vector, cfg)
	{
	}

	virtual void move() {
		if (abs(vector.x) >= config.speedFlag) {
			if (vector.x > 0) 
				coord.x += 1;
			else
				coord.x -= 1;
		}
		if (coord.x > config.position.x+config.width)
			coord.x = config.position.x-getWidth();
		if (coord.x < config.position.x-getWidth())
			coord.x = config.position.x+config.width;

		if (abs(vector.y) >= config.speedFlag) {
			if (vector.y > 0)
				coord.y += 1;
			else
				coord.y -= 1;
		}
		if (coord.y > config.position.y+config.height)
			coord.y = config.position.y-getHeight();
		if (coord.y < config.position.y-getHeight())
			coord.y = config.position.y+config.height;
	}


	SDL_bool checkCollision(SpaceObject& b) {
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

	~Asteroid() 
	{
	}

protected:
};



//#endif