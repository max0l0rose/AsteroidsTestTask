#pragma once
#include "Config.h"
#include "Bullet.h"

#include <vector>
//#include <list>
#include "Asteroids.h"

using namespace std;

class Bullets
{
private:
	vector<Bullet*> arr;
	Config& config;

	Asteroids& asteroids;

public:
	Bullets(Asteroids& asters, Config& cfg)
		: config(cfg), asteroids(asters)
	{
	}

	Bullet* createBullet(SDL_Point from, SDL_FPoint to, int speed) {
		Bullet* bullet = new Bullet(from, to, 1, config);
		arr.push_back(bullet);
		return bullet;
	}


	void draw() {
		for (size_t i = 0; i < arr.size(); i++) {
			//if (arr[i] != NULL)
				arr[i]->draw();
		}
	}

	
	void move() {
		for (size_t i = 0; i < arr.size(); i++) {
			if (arr[i] != NULL) {
				if (!arr[i]->move()) {
					delete arr[i];
					arr.erase(arr.begin() + i);
				}
			}
		}
	}

	
	void checkCollisions() {
		if (config.speedFlag < 3)
			return;

		for (size_t j = 0; j < arr.size(); j++)
		{
			//if (arr[j] == NULL)
			//	break;

			if (asteroids.checkCollisionsToObj(*arr[j])) 
			{

			}
		}
	}
	
	
	~Bullets() {
		for (size_t i = 0; i < arr.size(); i++) {
			if (arr[i] != NULL)
				delete arr[i];
		}
	}

};

