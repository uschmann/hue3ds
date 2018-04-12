#include <App.h>
#include <Controller/LightListController.h>
#include <Controller/LightColorController.h>

int main(int argc, char **argv)
{	
	App * app = App::getInstance();
	app->init();
	app->startController(new LightListController());
	app->run();
	return 0;
}
