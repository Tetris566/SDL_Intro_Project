#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>

#define GameName "RPG"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class SDLinit {
public:
	bool Setup();
	void Update();
	bool Cleanup();
};