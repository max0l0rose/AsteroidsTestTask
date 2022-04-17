#pragma once
//#ifndef asteroid
//#define asteroid

//#include <cstdlib>
#include <SDL_rect.h>

#include "Config.h"
#include "SpaceObject.h"
#include <vector>
//#include "AsteroidBig.h"
//#include "AsteroidSmall.h"

using namespace std;

class Asteroid : public SpaceObject
{
public:
	Asteroid(Config& cfg) 
		: SpaceObject(cfg)
	{
	}

	Asteroid(SDL_FPoint& coord, SDL_FPoint& vect, Config& cfg)
		: SpaceObject(coord, vect, cfg)
	{
	}

	
	virtual void boom(vector<Asteroid*>& arr) {
	}


	~Asteroid() 
	{
	}

protected:
};



//#endif