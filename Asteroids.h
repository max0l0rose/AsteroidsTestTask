#pragma once
//#ifndef asteroids
//#define asteroids

#include "Asteroid.h"
#include "AsteroidSmall.h"
#include "AsteroidBig.h"
#include <chrono>
#include <future>
//#include <array>
#include <iostream>
#include "MyUtil.h"

using namespace std;

class Asteroids
{
private:
	Config& config;
	mutex mtx;

public:
	vector<Asteroid*> arr;

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


	void deleteAsteroid(Asteroid& ast) {
		//arr.erase(
		//	remove_if(
		//		arr.begin(),
		//		arr.end(),
		//		//here comes the C++11 lambda:
		//		[&](Asteroid const& node) {
		//			return node == &ast;
		//		}
		//	),
		//	arr.end()
		//);
		
		arr.erase(remove(arr.begin(), arr.end(), &ast), arr.end());

		//arr.erase();
		delete &ast;
	}
	

	void deleteAsteroids() {
		for (auto iter = arr.begin(); iter != arr.end(); ) {
			delete *iter;
			iter = arr.erase(iter);
		}
	}


	void createAsteroids() {
		if (mtx.try_lock()) {
			deleteAsteroids();

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

			//cout << "arr.size init: " << arr.size() << endl;

			srand(time(NULL));
#define ASTEROIDS_QUANTITY 20
			for (size_t i = 0; i < ASTEROIDS_QUANTITY; i++) 
			{
				Asteroid* a = nullptr;
				if (rand() % 10 >= 5)
					a = new AsteroidSmall(config);
				else
					a = new AsteroidBig(config);
				SDL_Point p;
#define SHIP_ZONE_RADIUS 200
				SDL_Rect playerZoneRect = {
					config.position.x + config.width / 2 - SHIP_ZONE_RADIUS, config.position.x + config.height / 2 - SHIP_ZONE_RADIUS,
					SHIP_ZONE_RADIUS * 2, SHIP_ZONE_RADIUS * 2
				};
			mm:
				p.x = rand() % config.width;
				p.y = rand() % config.height;
				SDL_bool isInPlayerRect = SDL_PointInRect(&p, &playerZoneRect);
				if (isInPlayerRect == SDL_TRUE)
					goto mm;
				a->coord.x = p.x;
				a->coord.y = p.y;

				for (size_t j = 0; j < i; j++) {
					if (arr[j]->checkCollision(*a) == SDL_TRUE) {
						goto mm;
					}
				}

				int speedX, speedY;
			mm2:
				speedX = rand() % 6 - 3;
				speedY = rand() % 6 - 3;
				if (speedX == 0 && speedY == 0)
					goto mm2;
				a->vector.x = speedX;
				a->vector.y = speedY;

				arr.push_back(a);

				this_thread::sleep_for(chrono::milliseconds(50));
			}

			//if (arr.size() != ASTEROIDS_QUANTITY) {
			//	cout << "arr.size error !!!!!!!!!!!!!!!!!!!!!!: " << arr.size() << endl;
			//}

			mtx.unlock();
		}
	}

	void draw() {
		for (size_t i = 0; i < arr.size(); i++) {
			arr[i]->draw();
		}
	}

	void move() {
		for (size_t i = 0; i < arr.size(); i++) {
			arr[i]->move();
		}
	}

	void checkCollisionsToEachOther() {
		for (size_t i=0; i<arr.size(); i++) 
		{
			for (size_t j = i+1; j<arr.size(); j++)
			{
				//if (arr[j] == NULL)
				//	break;
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
						bounce(arr[i], arr[j]);
				}
			}
			if (arr[i]->collisionFlag > 0) 
				arr[i]->collisionFlag--;
		}
	}



	Asteroid* checkCollisionsToObj(SpaceObject& o) {
		if (config.speedFlag < 3)
			return nullptr;

		for (size_t j = 0; j < arr.size(); j++)
		{
			if (arr[j]->checkCollision(o) == SDL_TRUE) {
				return arr[j]; // collision
			}
		}

		return nullptr; // OK
	}


	void bounce(Asteroid* a, Asteroid* b) {
		SDL_FPoint tmpVec = a->vector;
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
		deleteAsteroids();
	}
};

//#endif
