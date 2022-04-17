#pragma once

#include "Asteroid.h"
//#include "Asteroids.h"
#include "AsteroidSmall.h"
#include "MyUtil.h"

class AsteroidBig : public Asteroid {
private:
	static Sprite* sprite;
	static Sprite* sprite2;
	static int width, height;

public:
	AsteroidBig(Config& cfg) : Asteroid(cfg) {
		init();
	}

	AsteroidBig(SDL_FPoint& coord, SDL_FPoint& vect, Config& cfg)
		: Asteroid(coord, vect, cfg)
	{
		init();
	}

	void init() {
		if (!sprite) {
			sprite = createSprite("data\\big_asteroid.png");
			getSpriteSize(sprite, width, height);
		}
		if (!sprite2) {
			sprite2 = createSprite("data\\big_asteroid2.png");
		}
	}


protected:
	Sprite* getSprite() const {
		return collisionFlag == 0 ? sprite : sprite2;
	}

	int getWidth() const {
		return width;
	}

	int getHeight() const {
		return height;
	}

};

