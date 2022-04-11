#pragma once
//#ifndef asteroids
//#define asteroids

//#include "Framework.h"
//#include "MyFramework.h"
#include "Asteroid.h"
#include "AsteroidSmall.h"
#include "AsteroidBig.h"
#include <array>

using namespace std;

class Asteroids
{
public:
	Asteroids() {
	}

	void init() {
		int w, h;
		getScreenSize(w, h);

		for (size_t i = 0; i < arr.size(); i++) {
			int type = rand() % 10;
			int x = rand() % w;
			int y = rand() % h;
			int speedX = rand() % 3-3;
			int speedY = rand() % 3-3;
			if (type>=5)
				arr[i] = new AsteroidSmall();
			else
				arr[i] = new AsteroidBig();
			arr[i]->coord.x = x;
			arr[i]->coord.y = y;
			arr[i]->moveVector.x = speedX;
			arr[i]->moveVector.y = speedY;
		}
	}

	array<Asteroid*, 20> arr;

	~Asteroids() {
		for (size_t i = 0; i < arr.size(); i++) {
			delete arr[i];
		}
	}

	void draw() {
		for (size_t i = 0; i < arr.size(); i++) {
			arr[i]->draw();
		}

	}
};

//#endif
