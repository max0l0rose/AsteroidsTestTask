#pragma once

#include <SDL_rect.h>
#include <iostream>

#include "SpaceObject.h"
#include "Asteroids.h"
#include "Config.h"

using namespace std;

class Player : public SpaceObject
{
	Sprite* sprite = NULL;
	int width = 0, height = 0;
	
	int speedDivider = 0;

	Asteroids& asteroids;

public:

	Player(Asteroids& ast, Config& cfg) 
		: SpaceObject(cfg), asteroids(ast)
	{
	}

	void init() {
		if (!sprite) {
			sprite = createSprite("data\\spaceship.png");
			getSpriteSize(sprite, width, height);
		}
		coord.x = (config.width - width) / 2;
		coord.y = (config.height - height) / 2;
	}

	void move() {
		if (vector.x != 0) {
			config.position.x += vector.x;
			coord.x += vector.x;
			if (speedDivider == 0) {
				if (vector.x > 0)
					vector.x -= 1;
				else
					vector.x += 1;
			}
			//cout << "config->position.x " << config.position.x << endl;
		}
		if (vector.y != 0) {
			config.position.y += vector.y;
			coord.y += vector.y;
			if (speedDivider == 0) {
				if (vector.y > 0)
					vector.y -= 1;
				else
					vector.y += 1;
			}
			//cout << "config->position.y " << config.position.y << endl;
		}
		if (--speedDivider==-1) {
			speedDivider = 20;
		}

	}


	//virtual void draw() {
	//	drawSprite(getSprite(), coord.x, coord.y);
	//}


	void checkCollisionsToAsteroids() 
	{
		Asteroid* ast = asteroids.checkCollisionsToObj(*this);
		if (ast != nullptr) {
			config.gameMode = GAME_STOPPED;
		}
	}


protected:
	Sprite* getSprite() const {
		return sprite;
	}

	int getWidth() const {
		return width;
	}

	int getHeight() const {
		return height;
	}

};

