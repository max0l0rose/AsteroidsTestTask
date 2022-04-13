#pragma once

#include "Asteroid.h"

class AsteroidBig : public Asteroid {
private:
	static Sprite* sprite;
	static Sprite* sprite2;
	static int width, height;

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
	virtual Sprite* getSprite() const {
		return collisionImmunity == 0 ? sprite : sprite2;
	}

	virtual int getWidth() const {
		return width;
	}
	virtual int getHeight() const {
		return height;
	}

public:
	AsteroidBig() : Asteroid() {
		init();
	}

	AsteroidBig(SDL_Point coord, SDL_Point vector) 
		: Asteroid(coord, vector)
	{
		init();
	}
};

