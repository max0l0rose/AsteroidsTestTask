#pragma once
//#ifndef asteroids
//#define asteroids

//#include "Framework.h"
//#include "MyFramework.h"
#include "Asteroid.h"
#include "AsteroidSmall.h"
#include "AsteroidBig.h"
#include <array>
#include <iostream>
//#include "Util.h"
#include "MyUtil.h"

using namespace std;

class Asteroids
{
private:
	array<Asteroid*, 20> arr;
	Config& config;

public:
	Asteroids(Config& cfg) 
		: config(cfg) 
	{
		for (size_t i = 0; i < arr.size(); i++)
			arr[i] = NULL;
	}

	void init() {
		int w, h;
		getScreenSize(w, h);

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
		for (size_t i = 0; i < arr.size(); i++) {
			int speedX, speedY;
			do {
			mm:
				int type = rand() % 10;
				int x = rand() % w;
				int y = rand() % h;
				if (type>=5)
					arr[i] = new AsteroidSmall(config);
				else
					arr[i] = new AsteroidBig(config);
				arr[i]->coord.x = x;
				arr[i]->coord.y = y;
				speedX = rand() % 6 - 3;
				speedY = rand() % 6 - 3;
				arr[i]->vector.x = speedX;
				arr[i]->vector.y = speedY;
				//SDL_Rect res;
				for (size_t j = 0; j < i; j++) {
					if (arr[i]->checkCollision(arr[j]) == SDL_TRUE) {
						goto mm;
					}
				}
			} while (speedX == 0 && speedY == 0);
		}
	}

	void draw() {
		for (size_t i = 0; i < arr.size(); i++) {
			//if (arr[i] != NULL)
				arr[i]->draw();
		}
	}

	void move() {
		for (size_t i = 0; i < arr.size(); i++) {
			//if (arr[i] != NULL)
				arr[i]->move();
		}
	}

	void checkCollisions() {
		//SDL_Rect res;
		for (size_t i = 0; i < arr.size()-1; i++) 
		{
			//if (arr[i] == NULL)
			//	break;
			//arr[i]->collisionRect = {0};
			for (size_t j = i+1; j < arr.size(); j++) 
			{
				if (
					//abs(arr[i]->moveVector.x) >= config->speedFlag
					//|| abs(arr[i]->moveVector.y) >= config->speedFlag
					//||
					//abs(arr[j]->moveVector.x) >= config->speedFlag
					//|| abs(arr[j]->moveVector.y) >= config->speedFlag
					config.speedFlag == 3
					)
				{
					if (arr[i]->checkCollision(arr[j]) == SDL_TRUE) {
						//cout << "flyApart: " << i << " " << j << endl;
						//if (res.w <= 2 || res.h <= 2) 
						{
							bounce(arr[i], arr[j]);
						}
						//if (res.w > 1 || res.h > 1) {
						//	//flyApart(arr[i], arr[j]);
						//	arr[i]->collisionRect = res;
						//	arr[j]->collisionRect = res;
						//}

						//delete arr[i]; delete arr[j];
						//arr[i] = arr[j] = NULL;
					}
				}
				//else {
				//	int a = 1;
				//}
			//else {
			//	arr[i]->collisionImmunity = arr[j]->collisionImmunity = 0;
			//}
			}
			//if (arr[i]->collisionImmunity > 0) {
			//	arr[i]->collisionImmunity--;
			//}
			//if (arr[j]->collisionImmunity > 0) {
			//	arr[j]->collisionImmunity--;
			//}
		}
	}

	void bounce(Asteroid* a, Asteroid* b) {
		//if (a->collision || b->collision) {
		//	a->collision = b->collision = false;
		//	return;
		//}

		SDL_Point tmpVec = a->vector;
		if (a->collisionImmunity == 0) {
			a->vector = b->vector;
			a->collisionImmunity = 000;
		}
		if (b->collisionImmunity == 0) {
			b->vector = tmpVec;
			b->collisionImmunity = 000;
		}
		//a->collision = b->collision = false;
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
