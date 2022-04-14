#pragma once
//#ifndef asteroids
//#define asteroids

#include "Asteroid.h"
#include "AsteroidSmall.h"
#include "AsteroidBig.h"
#include <chrono>
#include <future>
#include <array>
#include <iostream>
#include "MyUtil.h"

using namespace std;

class Asteroids
{
private:
	array<Asteroid*, 20> arr;
	Config& config;

	mutex mtx;

public:
	Asteroids(Config& cfg) 
		: config(cfg) 
	{
	}

	void init(int& doneFlag) {
		thread t1([this](int* doneFlag) { 
				createAsteroids(); 
				*doneFlag = 2; // 2 - game
			}, &doneFlag);
		t1.detach();
	}

	void createAsteroids() {
		if (mtx.try_lock()) {
			for (size_t i = 0; i < arr.size(); i++)
				arr[i] = NULL;

			//int w, h;
			//getScreenSize(w, h);

			//arr = {
			//	new AsteroidBig({ 500, 100 }, { 3, 0 }),
			//	new AsteroidBig({ 600, 100 }, { 1, 0 }),
			//	new AsteroidBig({ 500, 200 }, { 2, 0 }),
			//	new AsteroidBig({ 600, 200 }, { -1, 0 })
			//};

			//arr[2] = new AsteroidBig({ 300, 100 }, { 1, 0 });

			//arr = { 
			//	new AsteroidBig({ 100, 100 }, { 3, 3 }),
			//	new AsteroidBig({ 200, 100 }, { -3, 3 }),
			//	new AsteroidSmall({ 300, 100 }, { 3, 3 }),
			//	new AsteroidSmall({ 400, 100 }, { -3, 1 }),
			//	new AsteroidSmall({ 500, 100 }, { -3, 0 }),
			//	new AsteroidSmall({ 600, 100 }, { 0, 0 }),
			//	new AsteroidBig({ 800, 100 }, { 0, 0 }),
			//	new AsteroidBig({ 1000, 100 }, { 0, 0 })
			//};

			srand(time(NULL));
#define SHIP_ZONE_RADIUS 200
			SDL_Rect playerZoneRect = { config.width/2-SHIP_ZONE_RADIUS, config.height/2-SHIP_ZONE_RADIUS, SHIP_ZONE_RADIUS*2, SHIP_ZONE_RADIUS*2 };
			for (size_t i = 0; i < arr.size(); i++) {
				int speedX, speedY;
				do {
					SDL_Point p;
				mm:
					p.x = rand() % config.width;
					p.y = rand() % config.height;
					SDL_bool isInPlayerRect = SDL_PointInRect(&p, &playerZoneRect);
					if (isInPlayerRect == SDL_TRUE)
						goto mm;
					int type = rand() % 10;
					if (type >= 5)
						arr[i] = new AsteroidSmall(config);
					else
						arr[i] = new AsteroidBig(config);
					arr[i]->coord.x = p.x;
					arr[i]->coord.y = p.y;
					speedX = rand() % 6 - 3;
					speedY = rand() % 6 - 3;
					arr[i]->vector.x = speedX;
					arr[i]->vector.y = speedY;
					//SDL_Rect res;
					for (size_t j = 0; j < i; j++) {
						if (arr[i]->checkCollision(*arr[j]) == SDL_TRUE) {
							goto mm;
						}
					}
				} while (speedX == 0 && speedY == 0);

				this_thread::sleep_for(chrono::milliseconds(50));
			}

			mtx.unlock();
		}
	}

	void draw() {
		for (size_t i = 0; i < arr.size(); i++) {
			if (arr[i] != NULL)
				arr[i]->draw();
		}
	}

	void move() {
		for (size_t i = 0; i < arr.size(); i++) {
			if (arr[i] != NULL)
				arr[i]->move();
		}
	}

	void checkCollisionsToEachOther() {
		//SDL_Rect res;
		for (size_t i = 0; i < arr.size()-1; i++) 
		{
			if (arr[i] == NULL)
				break;
				
			for (size_t j = i+1; j < arr.size(); j++)
			{
				if (arr[j] == NULL)
					break;
				if (
					//abs(arr[i]->moveVector.x) >= config->speedFlag
					//|| abs(arr[i]->moveVector.y) >= config->speedFlag
					//||
					//abs(arr[j]->moveVector.x) >= config->speedFlag
					//|| abs(arr[j]->moveVector.y) >= config->speedFlag
					config.speedFlag == 3
					)
				{
					if (arr[i]->checkCollision(*arr[j]) == SDL_TRUE) 
					{
						bounce(arr[i], arr[j]);

						//delete arr[i]; delete arr[j];
						//arr[i] = arr[j] = NULL;
					}
				}
			}
			if (arr[i]->collisionFlag > 0) 
				arr[i]->collisionFlag--;
		}
	}



	void checkCollisionsToObj(SpaceObject& o) {
		if (config.speedFlag < 3)
			return;

		for (size_t j = 0; j < arr.size(); j++)
		{
			if (arr[j] == NULL)
				break;

			if (arr[j]->checkCollision(o) == SDL_TRUE) 
			{
				config.gameMode = GAME_STOPPED;
			}
		}
	}


	void bounce(Asteroid* a, Asteroid* b) {
		SDL_Point tmpVec = a->vector;
		a->vector = b->vector;
		if (a->collisionFlag == 0) 
#define COLLISION_TICKS 30
			a->collisionFlag = COLLISION_TICKS;

		b->vector = tmpVec;
		if (b->collisionFlag == 0) 
			b->collisionFlag = COLLISION_TICKS;
	}


	//void flyApart(Asteroid* a, Asteroid* b) {
	//	//config->setPause(true);

	//	//MyUtil::gerRndVector(a->moveVector);
	//	//a->coord.x += a->moveVector.x * 10;
	//	//a->coord.y += a->moveVector.y * 10;
	//}


	~Asteroids() {
		for (size_t i = 0; i < arr.size(); i++) {
			if (arr[i] != NULL)
				delete arr[i];
		}
	}
};

//#endif
