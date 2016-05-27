#pragma once
#include "Actor.h"

class Player : public Actor {
public:
	Player(std::string Name, int XPos, int YPos, int BaseDamage, int Health, int Score, LTexture Texture);
	void ModifyScore(int Amount);

	std::string name;
	//Animation class
	int baseDamage;
	int health;
	int score;
};