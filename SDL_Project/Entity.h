#pragma once
#include <string>
#include "LTexture.h"

class Entity {
public:
	Entity(int XPos, int YPos, LTexture Texture);
	void Move(int x, int y);
	LTexture texture;
	int xPos;
	int yPos;
};