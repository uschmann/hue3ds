#include <3ds.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include <App.h>
#include <FileSystem.h>
#include <Controller/Controller.h>
#include <Event.h>
#include <Screen.h>

App *App::INSTANCE = 0;



App::App() {
    this->isRunning = false;
    this->hue = new Hue();
    this->assetManager = new AssetManager();
}

App * App::getInstance() {
    if(!App::INSTANCE) {
        App::INSTANCE = new App();
    }
    return App::INSTANCE;
}

void App::init() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_ShowCursor(false);
    
    int screenFlags = SDL_SWSURFACE | SDL_BOTTOMSCR | SDL_CONSOLETOP;
	this->screen = SDL_SetVideoMode(BOTTOMSCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, screenFlags);
	
    httpcInit(4 * 1024 * 1024); 
    romfsInit();
    
    this->assetManager->init();

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
                case SDL_MOUSEBUTTONDOWN:
                    this->lastMouseDown = SDL_GetTicks();
                    break;
                case SDL_MOUSEBUTTONUP:
                    if((SDL_GetTicks() - this->lastMouseDown) < 150) {
                        SDL_MouseButtonEvent mouseEvent;
                        mouseEvent.x = event.button.x;
                        mouseEvent.y = event.button.y;

                        SDL_Event event;
                        event.type = SDL_USEREVENT;
                        event.user.code = TAP_EVENT;
                        event.user.data1 = &mouseEvent;;
                        SDL_PushEvent(&event);
                    }
                    break;
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
        if(this->controller != NULL) {
            this->controller->onDraw(this->screen);
        }
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