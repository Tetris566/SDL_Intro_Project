#include "Actor.h"

Actor::Actor(std::string Name, int XPos, int YPos, int BaseDamage, int Health, LTexture Texture) : Entity(XPos, YPos, Texture),
	name(Name),  baseDamage(BaseDamage), health(Health) {}

Actor::Actor(std::string Name, int XPos, int YPos, LTexture Texture) : Entity(XPos, YPos, Texture),
	name(Name) {}

void Actor::ApplyDamage(int Amount) {
	health -= Amount;
}

void Actor::DestroyActor() {

}