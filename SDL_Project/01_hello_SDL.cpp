/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>

#define GameName "RPG"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int X = 0, Y = 0;

//Main loop flag
bool quit = false;
bool GameRunning = true;

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

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//Loads individual image
SDL_Surface* loadSurface(std::string path);

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	} else {
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia() {
	//Loading success flag
	bool success = true;

	////Load PNG texture
	//gTexture = loadTexture("texture.png");
	//if (gTexture == NULL)
	//{
	//	printf("Failed to load texture image!\n");
	//	success = false;
	//}
	//
	//Load default surface
	//gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("press.bmp");
	//if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	//{
	//	printf("Failed to load default image!\n");
	//	success = false;
	//}
	//
	////Load space surface
	//gKeyPressSurfaces[KEY_PRESS_SURFACE_SPACE] = loadSurface("space.png");
	//if (gKeyPressSurfaces[KEY_PRESS_SURFACE_SPACE] == NULL)
	//{
	//	printf("Failed to load space image!\n");
	//	success = false;
	//}
	//
	////Load up surface
	//gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
	//if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
	//{
	//	printf("Failed to load up image!\n");
	//	success = false;
	//}
	//
	////Load down surface
	//gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
	//if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
	//{
	//	printf("Failed to load down image!\n");
	//	success = false;
	//}
	//
	////Load left surface
	//gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
	//if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
	//{
	//	printf("Failed to load left image!\n");
	//	success = false;
	//}
	//
	////Load right surface
	//gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");
	//if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
	//{
	//	printf("Failed to load right image!\n");
	//	success = false;
	//}

	return success;
}

void close()
{
	//Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	//Destroy window    
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Render(float deltaTime) {

}


void Update(float deltaTime){
	
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Set default current surface
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(gRenderer);
					SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
					SDL_RenderFillRect(gRenderer, &fillRect);
					SDL_Rect outlineRect = { X, Y, 100, 100 };
					SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
					SDL_RenderDrawRect(gRenderer, &outlineRect);
					//User presses a key
					if (e.type == SDL_KEYDOWN)
					{
						//Select surfaces based on key press
						switch (e.key.keysym.sym)
						{
						case SDLK_SPACE:
							//gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_SPACE];
							break;
					
						case SDLK_UP:
							//gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
							Y -= 10;
							break;
					
						case SDLK_DOWN:
							//gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
							Y += 10;
							break;
					
						case SDLK_LEFT:
							X -= 10;
							//gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
							break;
					
						case SDLK_RIGHT:
							X += 10;
							//gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
							break;
					
						default:
						//	gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
					}
				}

				////Apply the image stretched
				//SDL_Rect stretchRect;
				//stretchRect.x = 0;
				//stretchRect.y = 0;
				//stretchRect.w = SCREEN_WIDTH;
				//stretchRect.h = SCREEN_HEIGHT;
				//SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
				////SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
				//
				////Update the surface
				//SDL_UpdateWindowSurface(gWindow);

				//Clear screen
				//SDL_RenderClear(gRenderer);

				//Render texture to screen
				//SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}