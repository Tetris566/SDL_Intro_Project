#pragma once
#include "Entity.h"

class Actor : public Entity {
public:
	Actor(std::string Name, int XPos, int YPos, int BaseDamage, int Health, LTexture Texture);
	Actor(std::string Name, int XPos, int YPos, LTexture Texture);
	void ApplyDamage(int amount);
	void DestroyActor();
	std::string name;
	//Animation class
	int baseDamage;
	int health;
};