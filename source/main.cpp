#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Hue/Hue.h>
#include <Hue/Light.h>
#include <FileSystem.h>
#include <cJson.h>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
	gfxInitDefault();
	httpcInit(4 * 1024 * 1024); 
	//Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
	consoleInit(GFX_TOP, NULL);

	Hue *hue = new Hue();
	hue->discoverByNupnp();
	hue->setUser(FileSystem::readTextFile("hue.txt"));

	vector<Light> * lights = hue->getLights();
	int currentLight = 0;
	Light * light = &lights->at(0);

	// Main loop
	while (aptMainLoop())
	{	
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();
		
		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) break; // break in order to return to hbmenu

		if (kDown & KEY_LEFT) {
			currentLight --;
			if(currentLight < 0) {
				currentLight = lights->size()-1;
			}
			light = &lights->at(currentLight);
			light->print();
		}
		if (kDown & KEY_RIGHT) {
			currentLight ++;
			if(currentLight == lights->size()) {
				currentLight = 0;
			}
			light = &lights->at(currentLight);
			light->print();
		}
		if (kDown & KEY_A) {
			hue->setOnState(light->id, true);
		}
		if (kDown & KEY_B) {
			hue->setOnState(light->id, false);
		}

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}

	gfxExit();
	return 0;
}
