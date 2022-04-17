#pragma once
//#ifndef myf
//#define myf

#include <chrono>
#include <future>
#include <iostream>

#include "SDL.h"
#include "Config.h"
#include "Framework.h"
#include "Asteroids.h"

#include "Player.h"
#include "Bullets.h"

using namespace std;

class MyFramework : public Framework {
private:
	enum class Direction {
		NONE = 0,
		RIGHT = 1,
		LEFT = 2,
		DOWN = 4,
		UP = 8
	};

	Asteroids asteroids;
	Config config;
	Player player;
	Bullets bullets;

	Sprite* bg = NULL;
	static int fps;
	Direction direction = Direction::NONE;

	bool mouseButtonPressed = false;
	int mouseX = 0, mouseY = 0;
	Uint32 fireTicks = 0;

public:

	MyFramework() 
		: player(asteroids, config), asteroids(config), bullets(asteroids, config)
	{
	}


	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		config.width = width = 1200; // 1920;
		config.height = height = 800; //1080;
		fullscreen = false;
	}


	virtual bool Init() {
		fps = 0;

		config.gameMode == GAME_STOPPED;
		startGame(); 
		//player.init();

		bg = createSprite("data\\background_big.png");
		thread t2(showFps);
		t2.detach();

		showCursor(true);

		return true;
	}


	void startGame() {
		if (config.gameMode == GAME_INIT)
			return;
		config.gameMode = GAME_INIT;
		config.position = { 0 };
		player.init();
		asteroids.init(config.gameMode);
		bullets.deleteBullets();
	}


	virtual bool Tick() {
		//Uint32 ticks = SDL_GetTicks();
		//cout << ticks << " ";

		fps++;

		//drawTestBackground();
		drawSprite(bg, 0, 0);
		asteroids.draw();
		player.draw();
		bullets.draw();
		if (config.gameMode > GAME_STOPPED) {
			if (config.gameMode == GAME_GOES) {
				asteroids.checkCollisionsToEachOther();
				player.checkCollisionsToAsteroids();
				bullets.checkCollisions();
			}
			asteroids.move();
			player.move();
			bullets.move();
		}


		// move
		if ((int)direction & (int)Direction::RIGHT)
			player.vect.x = 2;
		if ((int)direction & (int)Direction::LEFT)
			player.vect.x = -2;
		if ((int)direction & (int)Direction::DOWN)
			player.vect.y = 2;
		if ((int)direction & (int)Direction::UP)
			player.vect.y = -2;


		// fire
		if (mouseButtonPressed && ++fireTicks % 10 == 0)
			fire();

#define DELAY 10
		this_thread::sleep_for(chrono::milliseconds(DELAY));
		return false;
	}

	
	void fire() {
		SDL_FPoint start = { player.coord.x, player.coord.y };
		SDL_FPoint dest = { mouseX, mouseY };
#define BULLET_SPEED 5
		bullets.createBullet(start, dest, BULLET_SPEED);
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		//cout << "onMouseMove: " << x << " " << y << " " << xrelative << " " << yrelative << endl;

		mouseX = x;
		mouseY = y;
	}


	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		//cout << "onMouseButtonClick: " << (int)button << " " << !isReleased << endl;

		if (mouseButtonPressed = !isReleased) {
			fire();
			fireTicks = 0;
		}

		//SDL_Window* window = SDL_CreateWindowFrom(0);
		//SDL_Window* window2 = SDL_GetWindowFromID(0);
		//SDL_Window* window3 = SDL_GetGrabbedWindow();
		//SDL_Window* window4 = SDL_GL_GetCurrentWindow();
		//SDL_Surface* surf = SDL_GetWindowSurface(window);
		//Uint32 i32 = SDL_GetWindowID(window);
		//SDL_Renderer* renderer = SDL_GetRenderer(window);
	}

	virtual void onKeyPressed(FRKey k) {
		if (config.gameMode == GAME_STOPPED || config.gameMode == GAME_WIN) {
			////if (m1.try_lock()) 
			////{
			//	thread t1([this]() {
			//		//m1.try_lock();
			//		//this_thread::sleep_for(chrono::milliseconds(1000));
			//		//m1.unlock();
			//		});
			//	t1.detach();
			////}
			startGame();
		}

		switch (k)
		{
		case FRKey::RIGHT:
			direction = (Direction)((int)direction | (int)Direction::RIGHT);
			break;
		case FRKey::LEFT:
			direction = (Direction)((int)direction | (int)Direction::LEFT);
			break;
		case FRKey::DOWN:
			direction = (Direction)((int)direction | (int)Direction::DOWN);
			break;
		case FRKey::UP:
			direction = (Direction)((int)direction | (int)Direction::UP);
			break;
		case FRKey::COUNT:
			//config->player.y--;
			break;
		default:
			break;
		}
		//cout << "direction: " << (int)direction << " " << endl;

		//key = k;
		//config->setPause(true);
		
		//cout << "onKeyPressed: " << (int)k << " " << endl;
	}

	virtual void onKeyReleased(FRKey k) {
		switch (k)
		{
		case FRKey::RIGHT:
			direction = (Direction)((int)direction & ~(int)Direction::RIGHT);
			break;
		case FRKey::LEFT:
			direction = (Direction)((int)direction & ~(int)Direction::LEFT);
			break;
		case FRKey::DOWN:
			direction = (Direction)((int)direction & ~(int)Direction::DOWN);
			break;
		case FRKey::UP:
			direction = (Direction)((int)direction & ~(int)Direction::UP);
			break;
		default:
			break;
		}
		//cout << "direction: " << (int)direction << " " << endl;

		//key = (FRKey)-1;
		//config->setPause(false);

		//cout << "onKeyReleased: " << (int)k << " " << endl;
	}

	virtual const char* GetTitle() override
	{
		return "Maxim's Asteroids";
	}

	static void showFps() {
		while (true) {
			cout << "fps=" << fps << endl;
			fps = 0;
			this_thread::sleep_for(chrono::milliseconds(1000));
		}
	}


	virtual void Close() 
	{
		cout << "Close()" << endl;
		//delete bg;
	}

	virtual ~MyFramework() 
	{
		cout << "~MyFramework()" << endl;
		//delete sprite;
	}

};


//#endif

