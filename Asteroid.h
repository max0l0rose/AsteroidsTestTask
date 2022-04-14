#pragma once

//#ifndef asteroid
//#define asteroid

//#include "MyFramework.h"

#include <cstdlib>

#include "Framework.h"
#include "Config.h"

#include <SDL_rect.h>

#include "SpaceObject.h"

//enum AsterType {
//	SMALL, BIG
//};

class Asteroid : public SpaceObject
{
public:
	int collisionImmunity = 0;
	//SDL_Rect collisionRect;
	//bool collision = false;

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
		if (coord.x > config.width)
			coord.x = -getWidth();
		if (coord.x < -getWidth())
			coord.x = config.width;

		if (abs(vector.y) >= config.speedFlag) {
			if (vector.y > 0)
				coord.y += 1;
			else
				coord.y -= 1;
		}
		if (coord.y > config.height)
			coord.y = -getHeight();
		if (coord.y < -getHeight())
			coord.y = config.height;
	}


	SDL_bool checkCollision(Asteroid* const b
									//, SDL_Rect& ri
								) {
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

		SDL_Rect ri;
		SDL_bool res = SDL_IntersectRect(&r1, &r2, &ri);
		
		//if (ri.w>1 || ri.h>1)
		//	collisionRect = ri;

		//if (ri.w > 2 && ri.h > 2)
		//	b->collision = collision = true;

		return res;
	}

	~Asteroid() 
	{
	}

protected:
};



//#endif