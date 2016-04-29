/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "SDLinit.h"
#include "GameManager.h"

int X = 0, Y = 0;

//Main loop flag
bool quit = false;
bool GameRunning = true;

extern int GAME_STATE = 0;

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL,
	KEY_PRESS_SURFACE_SPACE
};

//Event handler
SDL_Event e;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

extern SDL_Window* gWindow;

//The surface contained by the window
extern SDL_Surface* gScreenSurface;

//Loads individual image
SDL_Surface* loadSurface(std::string path);

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

//The images that correspond to a keypress
 extern SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);

//Current displayed image
 extern SDL_Surface* gCurrentSurface;

//The window renderer
 extern SDL_Renderer* gRenderer;

//Current displayed texture
SDL_Texture* gTexture = NULL;



void Render(float deltaTime) {

}


void Update(float deltaTime){
	
}

int main(int argc, char* args[])
{
	SDLinit sdlInit;
	GameManager gameManager;
	if (gameManager.Init()) {
		gameManager.Update();
	}

	return 0;
}