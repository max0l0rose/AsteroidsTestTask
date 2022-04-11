#pragma once
//#ifndef framAPI
//#define framAPI

#define FRAMEWORK_API extern "C" __declspec(dllimport)

// Bonus for any found bugs in the framework!

class Sprite;

FRAMEWORK_API Sprite* createSprite(const char* path);
FRAMEWORK_API void drawSprite(Sprite*, int x, int y);
FRAMEWORK_API void getSpriteSize(Sprite* s, int& w, int& h);
FRAMEWORK_API void destroySprite(Sprite* s);

FRAMEWORK_API void drawTestBackground();

FRAMEWORK_API void getScreenSize(int& w, int& h);

// Get the number of milliseconds since library initialization.
FRAMEWORK_API unsigned int getTickCount();

FRAMEWORK_API void showCursor(bool bShow);

//#endif

