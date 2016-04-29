#include "GameManager.h"
#include "SDLinit.h"

bool GameManager::Init() {
	SDLinit sdlInit;
	bool success = false;
	success = sdlInit.Setup();
	return success;
}

//TODO add DeltaTime
void GameManager::Update() {
	SDLinit sdlInit;
	sdlInit.Update();
}

void GameManager::Cleanup() {

}