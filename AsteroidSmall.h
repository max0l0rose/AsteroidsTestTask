#pragma once

#include "Asteroid.h"

class AsteroidSmall : public Asteroid {
private:
	static Sprite* sprite;
	static Sprite* sprite2;
	static int width, height;

public:
	AsteroidSmall(Config& cfg) : Asteroid(cfg) {
		init();
	}

	AsteroidSmall(SDL_FPoint coord, SDL_FPoint vector, Config& cfg)
		: Asteroid(coord, vector, cfg)
	{
		init();
	}

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

