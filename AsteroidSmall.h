#pragma once

#include "Asteroid.h"

class AsteroidSmall : public Asteroid {
private:
	static Sprite* sprite;
	static Sprite* sprite2;
	static int width, height;

	void init() {
		if (!sprite) {
			sprite = createSprite("data\\small_asteroid.png");
			getSpriteSize(sprite, width, height);
		}
		if (!sprite2) {
			sprite2 = createSprite("data\\small_asteroid2.png");
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
	AsteroidSmall() : Asteroid() {
		init();
	}

	AsteroidSmall(SDL_Point coord, SDL_Point mVector)
		: Asteroid(coord, mVector)
	{
		init();
	}
};

