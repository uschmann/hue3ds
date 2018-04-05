#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/HttpClient/HttpClient.h"
#include "include/FileSystem.h"

#include "cJson.h"

int main(int argc, char **argv)
{
	gfxInitDefault();
	httpcInit(4 * 1024 * 1024); 
	//Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
	consoleInit(GFX_TOP, NULL);

	HttpClient *client = new HttpClient();
	char * result = NULL;

	char * text = FileSystem::readTextFile("test.txt");
	printf(text);

	// Main loop
	while (aptMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) break; // break in order to return to hbmenu

		if (kDown & KEY_A) {
			result = client->put("http://192.168.1.204/api/qzkfZoi7znr4dpoMz876XW6Oz2LzBfjhVVqWLVGa/lights/6/state", "{\"on\":true}");
			printf(result);
			free(result);
		}
		if (kDown & KEY_B) {
			result = client->put("http://192.168.1.204/api/qzkfZoi7znr4dpoMz876XW6Oz2LzBfjhVVqWLVGa/lights/6/state", "{\"on\":false}");
			printf(result);
			free(result);
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
