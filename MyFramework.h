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

	Sprite* bg = NULL;
	static int fps;
	Direction direction = Direction::NONE;

public:

	MyFramework() 
		: player(asteroids, config), asteroids(config)
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

		startGame(); 

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
		asteroids.init(config.gameMode);
		player.init();
	}


	virtual bool Tick() {
		Uint32 ticks = SDL_GetTicks();
		//cout << ticks << " ";

		if (++config.speedFlag > 3) {
			config.speedFlag = 1;
		}

		fps++;

		//drawTestBackground();
		drawSprite(bg, 0, 0);
		asteroids.draw();
		if (config.gameMode > GAME_STOPPED) {
			player.draw();
			asteroids.checkCollisionsToEachOther();
			player.checkCollisionsToAsteroids();
			asteroids.move();
			player.move();
		}


		if ((int)direction & (int)Direction::RIGHT)
			player.vector.x = 3;
		if ((int)direction & (int)Direction::LEFT)
			player.vector.x = -3;
		if ((int)direction & (int)Direction::DOWN)
			player.vector.y = 3;
		if ((int)direction & (int)Direction::UP)
			player.vector.y = -3;

		this_thread::sleep_for(chrono::milliseconds(10));
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		cout << "onMouseButtonClick: " << (int)button << " " << !isReleased << endl;

		//SDL_Window* window = SDL_CreateWindowFrom(0);
		//SDL_Window* window2 = SDL_GetWindowFromID(0);
		//SDL_Window* window3 = SDL_GetGrabbedWindow();
		//SDL_Window* window4 = SDL_GL_GetCurrentWindow();
		//SDL_Surface* surf = SDL_GetWindowSurface(window);
		//Uint32 i32 = SDL_GetWindowID(window);
		//SDL_Renderer* renderer = SDL_GetRenderer(window);
	}

	virtual void onKeyPressed(FRKey k) {
		if (config.gameMode == 0) {
			thread t1([this]() {
				//this_thread::sleep_for(chrono::milliseconds(1000));
				startGame();
			});
			t1.detach();
			return;
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
		cout << "direction: " << (int)direction << " " << endl;

		//key = k;
		//config->setPause(true);
		cout << "onKeyPressed: " << (int)k << " " << endl;
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
		cout << "direction: " << (int)direction << " " << endl;

		//key = (FRKey)-1;
		//config->setPause(false);
		cout << "onKeyReleased: " << (int)k << " " << endl;
	}

	virtual const char* GetTitle() override
	{
		return "asteroids";
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

