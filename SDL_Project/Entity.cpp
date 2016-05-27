#include "Entity.h"

Entity::Entity(int XPos, int YPos, LTexture Texture) :
	xPos(XPos), yPos(YPos), texture(Texture) {}

void Entity::Move(int x, int y) {
	xPos += x;
	yPos += y;
}