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
	
	//int speedDivider = 0;

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


	bool move() {
		if (abs(vect.x) > 0.001) {
			config.position.x += vect.x;
			coord.x += vect.x;
			//if (speedDivider == 0) {
				if (vect.x > 0)
					vect.x -= 0.05;
				else
					vect.x += 0.05;
			//}
			//cout << "config->position.x " << config.position.x << endl;
		}
		if (abs(vect.y) > 0.001) {
			config.position.y += vect.y;
			coord.y += vect.y;
			//if (speedDivider == 0) {
				if (vect.y > 0)
					vect.y -= 0.05;
				else
					vect.y += 0.05;
			//}
			//cout << "config->position.y " << config.position.y << endl;
		}
		//if (--speedDivider==-1) {
		//	speedDivider = 3;
		//}

		return true;
	}


	//virtual void draw() {
	//	drawSprite(getSprite(), coord.x, coord.y);
	//}


	void checkCollisionsToAsteroids() 
	{
		//Asteroid* ast = 
		vector<Asteroid*>::iterator iter = asteroids.checkCollisionsToObj(*this);
		//if (ast != nullptr) 
		if (iter != asteroids.arr.end())
		{
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

