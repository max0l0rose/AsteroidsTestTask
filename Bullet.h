#pragma once

#include "Config.h"
#include "SpaceObject.h"

#include <cmath>

class Bullet : public SpaceObject
{
private:
	static Sprite* sprite;
	static Sprite* sprite2;
	static int width, height;

public:
	Bullet(Config& cfg)
		: SpaceObject(cfg)
	{
	}

	Bullet(SDL_FPoint& coord, SDL_FPoint& to, int speed, Config& cfg)
				: SpaceObject(coord, to, cfg) // to - not correct. just stub.
	{
		coord.x += config.position.x;
		coord.y += config.position.y;

		to.x += config.position.x;
		to.y += config.position.y;

		calcVector(to, speed);
		init();
	}


	void init() {
		if (!sprite) {
			sprite = createSprite("data\\bullet.png");
			getSpriteSize(sprite, width, height);
		}
		if (!sprite2) {
			sprite2 = createSprite("data\\bullet2.png");
		}
	}


	void calcVector(const SDL_FPoint& to, const float speed) {
		vect = { to.x - coord.x, to.y - coord.y };

		float m = std::fmax(abs(vect.x), abs(vect.y));
		vect.x /= m;
		vect.y /= m;

		vect.x *= speed;
		vect.y *= speed;
	}


	bool move() { // false - means - to delete
		if (coord.x > config.position.x + config.width ||
			coord.x < config.position.x - getWidth() ||
			coord.y > config.position.y + config.height ||
			coord.y < config.position.y - getHeight()
			) {
			// destroy
			return false;
		}

		//coord.x += vect.x;
		//coord.y += vect.y;
		SpaceObject::move();

		return true;
	}


	~Bullet()
	{
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

