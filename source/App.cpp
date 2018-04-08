#include <3ds.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include <App.h>
#include <FileSystem.h>
#include <Controller/Controller.h>

App *App::INSTANCE = 0;

const int TOPSCREEN_WIDTH = 400;
const int BOTTOMSCREEN_WIDTH = 340;
const int SCREEN_HEIGHT = 240;
const int SCREEN_BPP = 32;

App::App() {
    this->isRunning = false;
    this->hue = new Hue();
}

App * App::getInstance() {
    if(!App::INSTANCE) {
        App::INSTANCE = new App();
    }
    return App::INSTANCE;
}

void App::init() {
    SDL_Init(SDL_INIT_VIDEO);

    int screenFlags = SDL_SWSURFACE | SDL_BOTTOMSCR | SDL_CONSOLETOP;
	this->screen = SDL_SetVideoMode(BOTTOMSCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, screenFlags);
	httpcInit(4 * 1024 * 1024); 

	this->hue->discoverByNupnp();
	this->hue->setUser(FileSystem::readTextFile("hue.txt"));
}

void App::run() {
    this->isRunning = true;
    SDL_Event event;

    while (aptMainLoop() && isRunning)
	{	
		//Scan all the inputs. This should be done once for each frame
		while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_RETURN) { // Start
						this->isRunning = false;
					}
					break;
            }

            if(this->controller != NULL) {
                this->controller->onEvent(&event);
            }
        }

		// Do something here...
		SDL_Flip(this->screen);
	}
    
    SDL_Quit();
}

void App::startController(Controller * controller) {
    if(this->controller != NULL) {
        this->controller->onRemove();
        delete this->controller;
    }
    
    this->controller = controller;
    this->controller->onCreate(this);
    this->controller->onDraw(this->screen);
}