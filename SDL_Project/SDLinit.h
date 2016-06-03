#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>
#include "Timer.h"
#include <SDL_ttf.h>
#include <cmath>
#include "LTexture.h"
#include <sstream>
#include "Player.h"

#define GameName "RPG"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

extern int BackOffset_X;
extern int BackOffset_Y;

class SDLinit {
public:
	bool Setup();
	void Update();
	bool Cleanup();
};