#pragma once
#include "Actor.h"
#include "SDLinit.h"

class Player : public Actor {
public:
	Player(std::string Name, int XPos, int YPos, int BaseDamage, int Health, int Score, LTexture Texture);
	void ModifyScore(int Amount);
	void handleEvent(SDL_Event& e);
	void AdvMove();

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 10;

	std::string name;
	//Animation class
	int baseDamage;
	int health;
	int score;
	int VelX;
	int VelY;
	int BackOffset_X;
	int BackOffset_Y;
};