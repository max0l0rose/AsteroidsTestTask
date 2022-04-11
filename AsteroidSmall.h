#pragma once

#include "Asteroid.h"

class AsteroidSmall : public Asteroid {
private:
	static Sprite* sprite;
	static int width, height;

public:
	AsteroidSmall() : Asteroid() {
		if (!sprite) {
			sprite = createSprite("data\\small_asteroid.png");
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

