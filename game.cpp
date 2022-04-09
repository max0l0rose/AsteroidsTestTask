#include "Framework.h"
#include <iostream>
#include <chrono>
#include <future>

#include "Later.h"

using namespace std;

class MyFramework : public Framework {

	Sprite* sprite = NULL;
	static int fps;

	int width, height;

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		this->width = width = 500;
		this->height = height = 400;
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
		sprite = createSprite("data\\big_asteroid.png");
		//Later later_test2(1000, true, &test2, 101);
		thread t1(showFps);
		t1.detach();
		drawTestBackground();
		return true;
	}

	int x = 0;

	virtual bool Tick() {
		if (sprite != NULL) {
			drawSprite(sprite, x++, 10);
			if (x > width)
				x = -100;
			//cout << sin(x) << " ";
		}

		fps++;

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {

	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		cout << "onMouseButtonClick: " << (int)button << " " << !isReleased << endl;
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
		delete sprite;
	}

};


int MyFramework::fps = 0;


int main(int argc, char *argv[])
{
	return run(new MyFramework);
}
