#pragma once
//#ifndef asteroids
//#define asteroids

#include "Asteroid.h"
#include "AsteroidSmall.h"
#include "AsteroidBig.h"
#include <chrono>
#include <future>
//#include <array>
#include <vector>
#include <iostream>
#include "MyUtil.h"
#include <typeinfo>

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
				*doneFlag = GAME_GOES; 
			}, &doneFlag);
		t1.detach();
	}


	void deleteAsteroid(vector<Asteroid*>::iterator iter) {
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
		
		Asteroid* aster = (*iter);
		aster->boom(arr);
		
		//string s2 = typeid(AsteroidBig).name();
		AsteroidBig* bs = dynamic_cast<AsteroidBig*>(aster);
		if (bs != nullptr) { // it is big
			boomBigAsteroid(*bs);
		}

		delete *iter; // &ast;
		//arr.erase(remove(arr.begin(), arr.end(), &ast), arr.end());
		arr.erase(iter);
	}


	void boomBigAsteroid(Asteroid& bigAster) {
		AsteroidSmall* newAst = createSmallBoomAsteroid(bigAster);
		arr.push_back(newAst);
		//arr.insert(arr.begin(), newAst);
		newAst = createSmallBoomAsteroid(bigAster);
		arr.push_back(newAst);
	}

	AsteroidSmall* createSmallBoomAsteroid(Asteroid& astBig) {
		vector<Asteroid*>::iterator it;
		AsteroidSmall* astNew = nullptr;
		do {
			delete astNew;
			SDL_FPoint c = astBig.coord;
#define BOOM_RADIUS 50
			MyUtil::movePointRnd(c, BOOM_RADIUS, BOOM_RADIUS);
			SDL_FPoint v;
			MyUtil::getRndVector(v);
			astNew = new AsteroidSmall(c, v, config);
			it = checkCollisionsToObj(*astNew);
		} while (it != arr.end());
		return astNew;
	}


	void deleteAsteroids() {
		for (auto iter = arr.begin(); iter != arr.end(); ) {
			delete *iter;
			iter = arr.erase(iter);
		}
	}


	Asteroid* createRandomAsteroid() {
		Asteroid* a;
		if (rand() % 10 >= 5)
			a = new AsteroidSmall(config);
		else
			a = new AsteroidBig(config);
		return a;
	}


	void createAsteroids() {
		//if (mtx.try_lock()) 
		//{
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
				Asteroid* a = createRandomAsteroid();
				SDL_Point p;
#define SHIP_ZONE_RADIUS 200
				SDL_Rect playerZoneRect = {
					//config.position.x + 
					config.width / 2 - SHIP_ZONE_RADIUS, 
					//config.position.x + 
					config.height / 2 - SHIP_ZONE_RADIUS,
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

				for (int j = 0; j < i; j++) {
					if (arr[j]->checkCollision(*a) == SDL_TRUE) {
						goto mm;
					}
				}

				do {
					MyUtil::getRndVector(a->vect);
				} while (a->vect.x == 0 && a->vect.y == 0);

				mtx.lock();
				arr.push_back(a);
				mtx.unlock();

				this_thread::sleep_for(chrono::milliseconds(100));
			}


			if (arr.size() != ASTEROIDS_QUANTITY) {
				cout << "arr.size !!!!!!!!!!!!!!!!!!!!!!: " << arr.size() << endl;
			}

		//}
	}


	void draw() {
		//for (auto iter = arr.begin(); iter < arr.end(); iter++) {
		//	(*iter)->draw();
		//}

		bool init = false;
		if (config.gameMode == GAME_INIT) {
			mtx.lock();
			init = true;
		}
		//for (Asteroid* el : arr) {
		//	el->draw();
		//}
		for (int i = 0; i < arr.size(); i++) {
			arr[i]->draw();
		}
		if (init)
			mtx.unlock();

	}


	void move() {
		//for (auto iter = arr.begin(); iter < arr.end(); iter++ ) {
		//	(*iter)->move();
		//}

		if (config.gameMode == GAME_INIT)
			mtx.lock();
		for (Asteroid* el : arr) {
			el->move();
		}
		if (config.gameMode == GAME_INIT)
			mtx.unlock();

		//for (int i = 0; i < arr.size(); i++) {
		//	arr[i]->move();
		//}
	}


	void checkCollisionsToEachOther() {
		for (int i=0; i<arr.size(); i++) 
		{
			for (int j = i+1; j<arr.size(); j++)
			{
				if (arr[i]->checkCollision(*arr[j]) == SDL_TRUE) 
					bounce(arr[i], arr[j]);
			}
			if (arr[i]->collisionFlag > 0) 
				arr[i]->collisionFlag--;
		}
	}


	//Asteroid* 
	vector<Asteroid*>::iterator checkCollisionsToObj(const SpaceObject& o) {
		for (vector<Asteroid*>::iterator iter = arr.begin(); iter < arr.end(); iter++ ) {
			if ((* iter)->checkCollision(o) == SDL_TRUE) {
				return iter; // collision
			}
		}

		return arr.end();// nullptr; // OK
	}


	void bounce(Asteroid* a, Asteroid* b) {
		SDL_FPoint tmpVec = a->vect;
		a->vect = b->vect;
		if (a->collisionFlag == 0) 
#define COLLISION_TICKS 30
			a->collisionFlag = COLLISION_TICKS;

		b->vect = tmpVec;
		if (b->collisionFlag == 0) 
			b->collisionFlag = COLLISION_TICKS;
	}

	~Asteroids() {
		deleteAsteroids();
	}
};

//#endif
