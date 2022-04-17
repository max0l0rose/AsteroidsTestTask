#pragma once
#include "Config.h"
#include "Bullet.h"

#include <vector>
//#include <list>
#include "Asteroids.h"
#include <cassert>

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


	Bullet* createBullet(SDL_FPoint from, SDL_FPoint to, float speed) {
		from.x += 16;
		from.y -= 12;
		Bullet* bullet = new Bullet(from, to, speed, config);
		arr.push_back(bullet);
		return bullet;
	}


	void draw() const 
	{
		for (Bullet* el : arr) {
			el->draw();
		}
	}

	
	void move() {
		for (auto iter = arr.begin(); iter != arr.end(); ) {
			Bullet* b = *iter;
			if (!b->move()) 
			{
				//deleteBullet(*b);
				delete *iter;
				iter = arr.erase(iter);
			}
			else
				iter++;
		}
	}


	void deleteBullet(Bullet& bullet) {
		//static_assert(sizeof(void*) == 4, "64-bit code generation is not supported.");
		//throw invalid_argument("qqqq");
		
		arr.erase(remove(arr.begin(), arr.end(), &bullet), arr.end());
		delete &bullet;
	}


	void deleteBullets() {
		for (auto iter = arr.begin(); iter != arr.end(); ) {
			delete *iter;
			iter = arr.erase(iter);
		}
	}

	void checkCollisions() {
		//decltype
		for (auto iter = arr.begin(); iter != arr.end(); ++iter )
		{
			SpaceObject* bullet = *iter;
			//Asteroid* aster 
			vector<Asteroid*>::iterator aster_it = asteroids.checkCollisionsToObj(*bullet);
			if (aster_it != asteroids.arr.end())
			{
				asteroids.deleteAsteroid(aster_it);
				if (asteroids.arr.size() == 0)
					config.gameMode = GAME_WIN;

				delete *iter;
				//iter = arr.erase(iter);
				
				//std::advance(iter, 1);
				arr.erase(iter);
				 
				//iter = arr.begin();	 // another way to refresh iterator
 
				return;
			}
			//else
			//	iter++;
		}
	}
	
	
	~Bullets() {
		deleteBullets();
	}

};

