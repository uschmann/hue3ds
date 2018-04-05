#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Hue/Hue.h>
#include <FileSystem.h>
#include <cJson.h>

int main(int argc, char **argv)
{
	gfxInitDefault();
	httpcInit(4 * 1024 * 1024); 
	//Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
	consoleInit(GFX_TOP, NULL);

	Hue *hue = new Hue();
	printf("%s\n", hue->discoverByNupnp());
	printf("%s\n", hue->registerUser());

	// Main loop
	while (aptMainLoop())
	{	
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) break; // break in order to return to hbmenu

		// if (kDown & KEY_A) {
		// 	response = client->put("http://192.168.1.204/api/qzkfZoi7znr4dpoMz876XW6Oz2LzBfjhVVqWLVGa/lights/6/state", "{\"on\":true}");
		// 	printf("statuscode: %d\n", response->statuscode);
		// 	printf(response->data);
		// 	delete response;
		// }
		// if (kDown & KEY_B) {
		// 	response = client->put("http://192.168.1.204/api/qzkfZoi7znr4dpoMz876XW6Oz2LzBfjhVVqWLVGa/lights/6/state", "{\"on\":false}");
		// 	printf("statuscode: %d\n", response->statuscode);
		// 	printf(response->data);
		// 	delete response;
		// }

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}

	gfxExit();
	return 0;
}
