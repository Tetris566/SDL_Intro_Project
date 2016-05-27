#include "Player.h"

Player::Player(std::string Name, int XPos, int YPos, int BaseDamage, int Health, int Score, LTexture Texture) : Actor(Name, XPos, YPos, Texture),
	score(Score), VelX(0),VelY(0), BackOffset_X(0), BackOffset_Y(0) {} //Initialization List

void Player::ModifyScore(int Amount) {
	score += Amount;
}

void Player::handleEvent(SDL_Event& e) {
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_w: VelY -= DOT_VEL; break;
		case SDLK_s: VelY += DOT_VEL; break;
		case SDLK_a: VelX -= DOT_VEL; break;
		case SDLK_d: VelX += DOT_VEL; break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_w: VelY += DOT_VEL; break;
		case SDLK_s: VelY -= DOT_VEL; break;
		case SDLK_a: VelX += DOT_VEL; break;
		case SDLK_d: VelX -= DOT_VEL; break;
		}
	}
}

void Player::AdvMove() {
	//Move the dot left or right
	xPos += VelX;

	//If the dot went too far to the left or right
	if ((xPos < 0) || (xPos + 100 > SCREEN_WIDTH))
	{
		//Move back
		xPos -= VelX;
	}
	//Move the dot up or down
	yPos += VelY;

	//If the dot went too far up or down
	if ((yPos < 0) || (yPos + 100 > SCREEN_HEIGHT))
	{
		//Move back
		yPos -= VelY;
	}
	////////////////////////////////SCREEN CONSTARAINTS////////////////////
	// General Constraints
	if (xPos > SCREEN_WIDTH) {
		xPos = SCREEN_WIDTH;
	}
	if (xPos < 0) {
		xPos = 0;
	}
	if (yPos > SCREEN_HEIGHT) {
		yPos = SCREEN_HEIGHT;
	}
	if (yPos < 0) {
		yPos = 0;
	}
	//Up
	if (BackOffset_Y > 0) {
		BackOffset_Y = 0;
	}
	if (yPos < 100 && BackOffset_Y < 0) {
		yPos = 100;
		BackOffset_Y += 10;
	}
	//Down
	if (yPos > 280 && BackOffset_Y > -1500) {
		yPos = 280;
		BackOffset_Y -= 10;
	}
	if (BackOffset_Y < -1500) {
		BackOffset_Y = -1500;
	}
	//Left
	if (xPos < 130 && BackOffset_X < 0) {
		xPos = 130;
		BackOffset_X += 10;
	}
	if (BackOffset_X > 0) {
		BackOffset_X = 0;
	}
	//Right
	if (xPos > 410 && BackOffset_X > -1360) {
		xPos = 410;
		BackOffset_X -= 10;
	}
	if (BackOffset_X < -1360) {
		BackOffset_X = -1360;
	}
}