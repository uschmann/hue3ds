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

	HttpClient * client = new HttpClient();
	HttpResponse * response = NULL;

	Hue *hue = new Hue();
	printf("%s\n", hue->discoverByNupnp());
	char * username = FileSystem::readTextFile("hue.txt");
	printf("User: %s\n", username);
	hue->setUser(username);

	vector<Light> * lights = hue->getLights();
	printf("Found %i \n", lights->size());
	lights->at(0).print();
	for(int i = 0; i < lights->size(); i++) {
	//	lights->at(i).print();
	}

	// Main loop
	while (aptMainLoop())
	{	
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();
		
		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) break; // break in order to return to hbmenu

		if (kDown & KEY_A) {
			char url[255];
			sprintf(url, "http://192.168.1.204/api/%s/lights/6/state", username);
			response = client->put(url, "{\"on\":true}");
			
			printf("statuscode: %d\n", response->statuscode);
			printf(response->data);
			delete response;
		}
		if (kDown & KEY_B) {
			char url[255];
			sprintf(url, "http://192.168.1.204/api/%s/lights/6/state", username);
			response = client->put(url, "{\"on\":false}");
			
			printf("statuscode: %d\n", response->statuscode);
			printf(response->data);
			delete response;
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
