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


	Bullet* createBullet(SDL_FPoint from, SDL_FPoint to, int speed) {
		from.x += 16;
		from.y -= 12;
		Bullet* bullet = new Bullet(from, to, 5, config);
		arr.push_back(bullet);
		return bullet;
	}


	void draw() {
		for (size_t i = 0; i < arr.size(); i++) {
			arr[i]->draw();
		}
	}

	
	void move() {
		for (auto iter = arr.begin(); iter != arr.end(); ) {
			Bullet* b = *iter;
			if (!b->move()) {
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
		//throw invalid_argument("qqqqqqqqqqqqqqq");
		
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
		if (config.speedFlag < 3)
			return;

		for (auto b_iter = arr.begin(); b_iter != arr.end(); ) 
		{
			SpaceObject* q = *b_iter;
			Asteroid* ast = asteroids.checkCollisionsToObj(*q);
			if (ast != nullptr) 
			{
				asteroids.deleteAsteroid(*ast);
				if (asteroids.arr.size() == 0)
					config.gameMode = GAME_WIN;

				delete *b_iter;
				b_iter = arr.erase(b_iter);
			}
			else
				b_iter++;
		}
	}
	
	
	~Bullets() {
		deleteBullets();
	}

};

