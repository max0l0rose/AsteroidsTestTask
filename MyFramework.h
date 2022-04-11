#pragma once
//#ifndef myf
//#define myf

//#include "Later.h"

//#include "SDL.h"
#include "Framework.h"

#include "Asteroids.h"

#include <iostream>
#include <chrono>
#include <future>
#include "Config.h"

using namespace std;

class MyFramework : public Framework {

	Asteroids asteroids;

	Config config;

	//Sprite* sprite = NULL;
	static int fps;
public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		config.width = width = 800;
		config.height = height = 600;
		fullscreen = false;
	}


	static void showFps() {
		while (true) {
			cout << "fps=" << fps << endl;
			fps = 0;
			this_thread::sleep_for(chrono::milliseconds(1000));
		}
	}


	virtual bool Init() {
		fps = 0;
		asteroids.init();
		//sprite = createSprite("data\\big_asteroid.png");
		////Later later_test2(1000, true, &test2, 101);
		thread t1(showFps);
		t1.detach();

		return true;
	}

	int x = 0;

	virtual bool Tick() {
		//Uint32 q = SDL_GetTicks();
		//cout << q << " tics " << endl;

		//if (sprite != NULL) {
		//	drawSprite(sprite, x++, 10);
		//	if (x > width)
		//		x = -100;
		//}

		fps++;

		//drawTestBackground();
		asteroids.draw();

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
		cout << "onKeyPressed: " << (int)k << " " << endl;
	}

	virtual void onKeyReleased(FRKey k) {
		cout << "onKeyReleased: " << (int)k << " " << endl;
	}

	virtual const char* GetTitle() override
	{
		return "asteroids";
	}

	void Close() {
		//delete sprite;
	}

	~MyFramework() {
		//delete sprite;
	}

};


//#endif

