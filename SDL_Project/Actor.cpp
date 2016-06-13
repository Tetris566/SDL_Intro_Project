#include "Actor.h"
#include "SDLinit.h"


Actor::Actor(std::string Name, int XPos, int YPos, int BaseDamage, int Health, LTexture Texture) : Entity(XPos, YPos, Texture),
	name(Name),  baseDamage(BaseDamage), health(Health)
{
	Collider.w = 100;//Texture.getWidth();
	Collider.h = 100;//Texture.getHeight();
	Collider.x = xPos;
	Collider.y = yPos;
}

Actor::Actor(std::string Name, int XPos, int YPos, LTexture Texture) : Entity(XPos, YPos, Texture),
	name(Name) 
{
	Collider.w = 100;// Texture.getWidth();
	Collider.h = 100;// Texture.getHeight();
	Collider.x = xPos;
	Collider.y = yPos;
}

void Actor::ApplyDamage(int Amount) {
	health -= Amount;
}

void Actor::DestroyActor() {
	delete[] this;
}

bool Actor::Collide(SDL_Rect a, SDL_Rect b) {
		//The sides of the rectangles
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		//Calculate the sides of rect A
		leftA = a.x;
		rightA = a.x + a.w;
		topA = a.y;
		bottomA = a.y + a.h;

		//Calculate the sides of rect B
		leftB = b.x +BackOffset_X;
		rightB = b.x + b.w +BackOffset_X;
		topB = b.y +BackOffset_Y;
		bottomB = b.y + b.h +BackOffset_Y;
		//If any of the sides from A are outside of B
		if (bottomA <= topB)
		{
			return false;
		}

		if (topA >= bottomB)
		{
			return false;
		}

		if (rightA <= leftB)
		{
			return false;
		}

		if (leftA >= rightB)
		{
			return false;
		}

		//If none of the sides from A are outside B
		return true;
	}

bool Actor::CollideRevOff(SDL_Rect a, SDL_Rect b) {
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x + BackOffset_X;
	rightA = a.x + a.w + BackOffset_X;
	topA = a.y + BackOffset_Y;
	bottomA = a.y + a.h + BackOffset_Y;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

void Actor::CheckCollision(Actor other) 
{
	Collider.x = xPos;

	if ((xPos < 0) || (xPos + 100 > SCREEN_WIDTH) || CollideRevOff(Collider, other.Collider))
	{
		//printf("EnemyHit");
		Collider.x = xPos;
	}

	Collider.y = yPos;

	if ((yPos < 0) || (yPos + 100 > SCREEN_HEIGHT) || CollideRevOff(Collider, other.Collider))
	{
		//printf("EnemyHit");
		Collider.y = yPos;
	}
}