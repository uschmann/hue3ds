#include <App.h>
#include <Controller/Controller.h>

int main(int argc, char **argv)
{	
	App * app = App::getInstance();
	app->init();
	app->startController(new Controller());
	app->run();
	return 0;
}
