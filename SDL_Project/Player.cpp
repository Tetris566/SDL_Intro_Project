#include "Player.h"

Player::Player(std::string Name, int XPos, int YPos, int BaseDamage, int Health, int Score, LTexture Texture) : Actor(Name, XPos, YPos, Texture),
	score(Score) {} //Initialization List

void Player::ModifyScore(int Amount) {
	score += Amount;
}