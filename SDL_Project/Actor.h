#pragma once
//#include "SDLinit.h"
#include "Entity.h"

class Actor : public Entity {
public:
	Actor(std::string Name, int XPos, int YPos, int BaseDamage, int Health, LTexture Texture);
	Actor(std::string Name, int XPos, int YPos, LTexture Texture);
	void ApplyDamage(int amount);
	void DestroyActor();
	void CheckCollision(Actor other);
	bool Collide(SDL_Rect colliderA, SDL_Rect colliderB);
	bool CollideRevOff(SDL_Rect colliderA, SDL_Rect colliderB);
	std::string name;
	//Animation class
	int baseDamage;
	int health;
	SDL_Rect Collider;
};