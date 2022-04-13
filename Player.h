#pragma once

#include <SDL_rect.h>

#include "SpaceObject.h"

#include "Config.h"

class Player : public SpaceObject
{
	static Sprite* sprite;
	static int width, height;

public:
	SDL_Point coord = {0};
	SDL_Point vector = {0};
	int screenX, screenY;

	void init() {
		if (!sprite) {
			sprite = createSprite("data\\spaceship.png");
			getSpriteSize(sprite, width, height);

			screenX = (Config::width - width) / 2;
			screenY = (Config::height - height) / 2;
		}
	}

	void move() {
		if (vector.x != 0) {
			coord.x += vector.x;
			if (vector.x>0)
				vector.x--;
			else
				vector.x++;
		}
		if (vector.y != 0) {
			coord.y += vector.y;
			if (vector.y > 0)
				vector.y--;
			else
				vector.y++;
		}
	}

	void draw() {
		drawSprite(getSprite(), screenX, screenY);
	}

	virtual Sprite* getSprite() const {
		return sprite;
	}

	virtual int getWidth() const {
		return width;
	}
	virtual int getHeight() const {
		return height;
	}

};

