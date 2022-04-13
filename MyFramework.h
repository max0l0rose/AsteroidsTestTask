#pragma once
//#ifndef myf
//#define myf

//#include "Later.h"

#include <chrono>
#include <future>
#include "Config.h"
#include <iostream>

#include "SDL.h"
#include "Framework.h"
#include "Asteroids.h"

#include "Player.h"


using namespace std;

class MyFramework : public Framework {

	Asteroids asteroids;

	//Config config;

	Player player;

	Sprite* bg = NULL;
	static int fps;
public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		Config::width = width = 1200; // 1920;
		Config::height = height = 800; //1080;
		fullscreen = false;
	}


	virtual bool Init() {
		fps = 0;
		asteroids.init();
		player.init();

		bg = createSprite("data\\background_big.png");
		////Later later_test2(1000, true, &test2, 101);
		thread t1(showFps);
		t1.detach();

		showCursor(true);

		//Config::player = { 0 };
		//Config::playerVect = { 0 };

		return true;
	}


	virtual bool Tick() {
		Uint32 ticks = SDL_GetTicks();
		//cout << ticks << " ";

		if (++Config::speedFlag > 3) {
			Config::speedFlag = 1;
		}

		fps++;

		//drawTestBackground();
		if (!Config::getPause()) {
			asteroids.checkCollisions();
			asteroids.move();
		}
		drawSprite(bg, 0, 0);
		asteroids.draw();
		player.draw();

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
		switch (k)
		{
		case FRKey::RIGHT:
			//Config::playerVect.x = 20;
			break;
		case FRKey::LEFT:
			//Config::player.x = -20;
			break;
		case FRKey::DOWN:
			//Config::player.y = 20;
			break;
		case FRKey::UP:
			//Config::player.y = -20;
			break;
		case FRKey::COUNT:
			//Config::player.y--;
			break;
		default:
			break;
		}
		//Config::setPause(true);
		cout << "onKeyPressed: " << (int)k << " " << endl;
	}

	virtual void onKeyReleased(FRKey k) {
		//Config::setPause(false);
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

