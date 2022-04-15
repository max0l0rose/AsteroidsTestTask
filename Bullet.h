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

	Bullet(SDL_FPoint coord, SDL_FPoint to, int speed, Config& cfg)
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


	void calcVector(SDL_FPoint& to, int speed) {
		vector = { to.x - coord.x, to.y - coord.y };

		float m = std::fmax(abs(vector.x), abs(vector.y));
		vector.x /= m;
		vector.y /= m;

		vector.x *= speed;
		vector.y *= speed;
	}


	virtual bool move() { // false - means - to delete
		if (coord.x > config.position.x + config.width ||
			coord.x < config.position.x - getWidth() ||
			coord.y > config.position.y + config.height ||
			coord.y < config.position.y - getHeight()
			) {
			// destroy
			return false;
		}

		//if (abs(vector.x) >= config.speedFlag) 
		{
			//if (vector.x > 0.001)
				coord.x += vector.x;
			//else
				//coord.x -= vector.y;
		}

		//if (abs(vector.y) >= config.speedFlag) 
		{
			//if (vector.y > 0.001)
				coord.y += vector.y;
			//else
				//coord.y -= vector.y;
		}

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

