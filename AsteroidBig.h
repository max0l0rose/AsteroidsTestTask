#pragma once

#include "Asteroid.h"

class AsteroidBig : public Asteroid {
private:
	static Sprite* sprite;
	static int width, height;

public:
	AsteroidBig() : Asteroid() {
		if (!sprite) {
			sprite = createSprite("data\\big_asteroid.png");
			getSpriteSize(sprite, width, height);
		}
	}

	virtual Sprite* getSprite() {
		return sprite;
	}

	virtual int getWidth() {
		return width;
	}
	virtual int getHeight() {
		return height;
	}

};

