#pragma once
//#ifndef myf
//#define myf

//#include "Later.h"

#include "SDL.h"
#include "Framework.h"

#include "Asteroids.h"

#include <chrono>
#include <future>
#include "Config.h"
#include <iostream>

using namespace std;

class MyFramework : public Framework {

	Asteroids asteroids;

	Config config;

	Sprite* bg = NULL;
	static int fps;
public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		config.width = width = 1000; // 1920;
		config.height = height = 800; //1080;
		fullscreen = false;
	}


	virtual bool Init() {
		fps = 0;
		asteroids.init();
		bg = createSprite("data\\background_big.png");
		////Later later_test2(1000, true, &test2, 101);
		thread t1(showFps);
		t1.detach();

		showCursor(true);

		return true;
	}

	virtual bool Tick() {
		if (pause)
			return false;

		Uint32 ticks = SDL_GetTicks();
		//cout << ticks << " ";

		if (++config.speedFlag > 3) {
			config.speedFlag = 1;
			if (//ticks > 2000 && 
				config.speedFlag)
				asteroids.checkCollisions();
		}

		fps++;

		//drawTestBackground();
		asteroids.move();
		drawSprite(bg, 0, 0);
		asteroids.draw();

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

	bool pause = false;
	virtual void onKeyPressed(FRKey k) {
		pause = !pause;
		cout << "onKeyPressed: " << (int)k << " " << endl;
	}

	virtual void onKeyReleased(FRKey k) {
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

