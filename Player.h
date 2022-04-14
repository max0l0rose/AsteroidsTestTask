#pragma once

#include <SDL_rect.h>
#include <iostream>

#include "SpaceObject.h"

#include "Config.h"

using namespace std;

class Player : public SpaceObject
{
	Sprite* sprite = NULL;
	int width = 0, height = 0;

public:

	Player(Config& cfg) 
		: SpaceObject(cfg)
	{
	}

	void init() {
		if (!sprite) {
			sprite = createSprite("data\\spaceship.png");
			getSpriteSize(sprite, width, height);

			coord.x = (config.width - width) / 2;
			coord.y = (config.height - height) / 2;
		}
	}

	void move() {
		if (vector.x != 0) {
			config.position.x += vector.x;
			if (vector.x>0)
				vector.x--;
			else
				vector.x++;
			cout << "config->position.x" << config.position.x << endl;
		}
		if (vector.y != 0) {
			config.position.y += vector.y;
			if (vector.y > 0)
				vector.y--;
			else
				vector.y++;
			cout << "config->position.y" << config.position.y << endl;
		}
	}

	virtual void draw() {
		drawSprite(getSprite(), coord.x, coord.y);
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

