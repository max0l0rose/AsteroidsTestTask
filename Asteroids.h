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

using namespace std;

class Asteroids
{
	private:
	array<Asteroid*, 6> arr;

public:
	Asteroids() {
	}

	void init() {
		int w, h;
		getScreenSize(w, h);

		//arr[0] = new AsteroidBig({ 100, 100 }, { 3, 0 });
		//arr[1] = new AsteroidBig({ 200, 100 }, { 2, 0 });
		//arr[2] = new AsteroidBig({ 300, 100 }, { 1, 0 });

		arr[0] = new AsteroidBig({ 100, 100 }, { 3, 3 });
		arr[1] = new AsteroidBig({ 200, 100 }, { -3, 3 });

		arr[2] = new AsteroidSmall({ 300, 100 }, { 3, 3 });
		arr[3] = new AsteroidSmall({ 400, 100 }, { -3, 1 });
		arr[4] = new AsteroidSmall({ 500, 100 }, { -3, 0 });
		arr[5] = new AsteroidSmall({ 800, 100 }, { 0, 0 });

		//for (size_t i = 0; i < arr.size(); i++) {
		//	int type = rand() % 10;
		//	int x = rand() % w;
		//	int y = rand() % h;
		//	if (type>=5)
		//		arr[i] = new AsteroidSmall();
		//	else
		//		arr[i] = new AsteroidBig();
		//	arr[i]->coord.x = x;
		//	arr[i]->coord.y = y;
		//	int speedX, speedY;
		//	do {
		//		speedX = rand() % 6 - 3;
		//		speedY = rand() % 6 - 3;
		//		arr[i]->moveVector.x = speedX;
		//		arr[i]->moveVector.y = speedY;
		//	} while (speedX == 0 && speedY == 0);
		//}
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
		for (size_t i = 0; i < arr.size()-1; i++) {
			for (size_t j = i+1; j < arr.size(); j++) {
				//if (arr[i] != NULL && arr[j] != NULL) 
				{
					if (arr[i]->checkCollision(arr[j]) == SDL_TRUE) {
						//cout << "flyApart: " << i << " " << j << endl;
						flyApart(arr[i], arr[j]);

						//delete arr[i]; delete arr[j];
						//arr[i] = arr[j] = NULL;
					}
					//else {
					//	arr[i]->collisionImmunity = arr[j]->collisionImmunity = 0;
					//}
				}
				if (arr[i]->collisionImmunity > 0) {
					arr[i]->collisionImmunity--;
				}
				if (arr[j]->collisionImmunity > 0) {
					arr[j]->collisionImmunity--;
				}
			}
		}
	}

	void flyApart(Asteroid* a, Asteroid* b) {
		if (a->moveVector.x * b->moveVector.x < 0) {
			if (a->collisionImmunity == 0) {
				a->moveVector.x = -a->moveVector.x;
				a->collisionImmunity = 60;
			}

			if (b->collisionImmunity == 0) {
				b->moveVector.x = -b->moveVector.x;
				b->collisionImmunity = 60;
			}
		}
		else {
			if (a->moveVector.x > b->moveVector.x) {
				if (a->collisionImmunity == 0) {
					a->moveVector.x--;
					a->collisionImmunity = 60;
				}

				if (b->collisionImmunity == 0) {
					b->moveVector.x++;
					b->collisionImmunity = 60;
				}
			}
			else {
				if (a->collisionImmunity == 0) {
					a->moveVector.x++;
					a->collisionImmunity = 60;
				}

				if (b->collisionImmunity == 0) {
					b->moveVector.x--;
					b->collisionImmunity = 60;
				}
			}
		}

		if (a->moveVector.y * b->moveVector.y < 0) {
			if (a->collisionImmunity == 0) {
				a->moveVector.y = -a->moveVector.y;
				a->collisionImmunity = 60;
			}
			if (b->collisionImmunity == 0) {
				b->moveVector.y = -b->moveVector.y;
				b->collisionImmunity = 60;
			}
		}
		else {
			if (a->moveVector.y > b->moveVector.y) {
				if (a->collisionImmunity == 0) {
					a->moveVector.y--;
					a->collisionImmunity = 100;
				}

				if (b->collisionImmunity == 0) {
					b->moveVector.y++;
					b->collisionImmunity = 100;
				}
			}
			else {
				if (a->collisionImmunity == 0) {
					a->moveVector.y++;
					a->collisionImmunity = 100;
				}

				if (b->collisionImmunity == 0) {
					b->moveVector.y--;
					b->collisionImmunity = 100;
				}
			}
		}
	}


	~Asteroids() {
		for (size_t i = 0; i < arr.size(); i++) {
			if (arr[i] != NULL)
				delete arr[i];
		}
	}
};

//#endif
