#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Hue/Hue.h>
#include <Hue/Light.h>
#include <FileSystem.h>
#include <cJson.h>
#include <vector>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

using namespace std;

const int TOPSCREEN_WIDTH = 400;
const int BOTTOMSCREEN_WIDTH = 340;
const int SCREEN_HEIGHT = 240;
const int SCREEN_BPP = 16;

int main(int argc, char **argv)
{
	bool isRunning = true;
	SDL_Surface *screen = NULL;
	SDL_Event event;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		return 1;
	}

	int screenFlags = SDL_SWSURFACE | SDL_BOTTOMSCR | SDL_CONSOLETOP;
	screen = SDL_SetVideoMode(BOTTOMSCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, screenFlags);
	httpcInit(4 * 1024 * 1024); 

	Hue *hue = new Hue();
	hue->discoverByNupnp();
	hue->setUser(FileSystem::readTextFile("hue.txt"));

	vector<Light> * lights = hue->getLights();
	int currentLight = 0;
	Light light = lights->at(0);

	vector<Group> * groups = hue->getGroups();
	printf("Groups %d \n", groups->size());
	printf("name %s \n", groups->at(0).name);
	printf("name %s \n", groups->at(1).name);

	// Main loop
	while (aptMainLoop() && isRunning)
	{	
		//Scan all the inputs. This should be done once for each frame
		while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_RETURN) { // Start
						isRunning = false;
					}
					break;
            }
        }

		// Do something here...

		SDL_Flip(screen);
	}

	SDL_Quit();
	return 0;
}
