#include "SDLinit.h"

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

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Renderer* gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
//SDL_Texture* gCurrentSurface = NULL;
//SDL_Texture* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
TTF_Font *gFont = NULL;

SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else {
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

//Scene textures
LTexture gFooTexture;
LTexture gBackgroundTexture;
LTexture gTextTexture;
LTexture gCurrentSurface;
LTexture gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

Player player("thePlayer", 240, 190, 10, 100, 0, gCurrentSurface);

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
				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}

				//Player Setup
				//player.Move(10,10);
			}
		}
	}

	return success;
}



bool loadMedia() {
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont("lazy.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if (!gTextTexture.loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	//Load Foo' texture
	if (!gFooTexture.loadFromFile("Assets/Images/Player.png"))
	{
		printf("Failed to load Foo' texture image!\n");
		success = false;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	success = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT].loadFromFile("Assets/Images/Player.png");

	//Load up surface
	success = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP].loadFromFile("Assets/Images/PlayerUp.png");

	//Load down surface
	success = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN].loadFromFile("Assets/Images/PlayerDown.png");

	//Load left surface
	success = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT].loadFromFile("Assets/Images/PlayerLeft.png");

	//Load right surface
	success = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT].loadFromFile("Assets/Images/PlayerRight.png");

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Load background texture
	if (!gBackgroundTexture.loadFromFile("Assets/Images/Backdrop.png"))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}

	return success;
}


bool SDLinit::Setup() {

	bool success = true;

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
		success = false;
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
			success = false;
		}
		else
		{
			
		}
	}
	return success;
}

//TODO add DeltaTime
void SDLinit::Update() {
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//Set text color as black
	SDL_Color textColor = { 0, 0, 0, 255 };

	//The frames per second timer
	LTimer fpsTimer;

	//The frames per second cap timer
	LTimer capTimer;

	//In memory text stream
	std::stringstream timeText;

	//Start counting frames per second
	int countedFrames = 0;
	fpsTimer.start();

	//Set default current surface
	gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];


	//While application is running
	while (!quit)
	{
		//Start cap timer
		capTimer.start();
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			
			else if (e.type == SDL_KEYDOWN)
			{
				//Select surfaces based on key press
				switch (e.key.keysym.sym)
				{
				case SDLK_w:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
					break;

				case SDLK_s:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
					break;

				case SDLK_a:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
					break;

				case SDLK_d:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
					break;

				default:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
					break;
				}
			}
			else if (e.type == SDL_KEYUP) {
				switch (e.key.keysym.sym) {
				default:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
					break;
				}
			} player.handleEvent(e);
		}
		////////////////////////////////////////////////////////////////////////
		//Calculate and correct fps
		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}

		//Set text to be rendered
		timeText.str("");
		timeText << "Average Frames Per Second (With Cap) " << avgFPS;

		//Render text
		if (!gTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor))
		{
			printf("Unable to render FPS texture!\n");
		}
		////////////////////////////////////////////////////////////////////////

		player.AdvMove();

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//Render background texture to screen
		gBackgroundTexture.render(player.BackOffset_X, player.BackOffset_Y);

		//Render Character to the screen
		gCurrentSurface.render(player.xPos,player.yPos);

		gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTextTexture.getHeight()) / 10);

		//Update screen
		SDL_RenderPresent(gRenderer);
		++countedFrames;
		//If frame finished early
		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}
}

bool SDLinit::Cleanup() {
	//SDL_Delay(2000);
	//Free loaded images
	gCurrentSurface.free();
	gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL].free();
	gFooTexture.free();
	gBackgroundTexture.free();

	//Destroy window    
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	return true;
}