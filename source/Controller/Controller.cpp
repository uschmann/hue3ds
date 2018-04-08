#include <stdio.h>
#include <Controller/Controller.h>

void Controller::onCreate(App * app) {
    printf("onCreate\n");
    this->app = app;
}

void Controller::onEvent(SDL_Event * event) {
    printf("onEvent\n");
}

void Controller::onDraw(SDL_Surface *screen) {
    printf("onDraw\n");
}