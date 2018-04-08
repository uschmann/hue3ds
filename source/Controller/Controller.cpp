#include <stdio.h>
#include <Controller/Controller.h>

void Controller::onCreate(App * app) {
    this->app = app;
}

void Controller::onEvent(SDL_Event * event) {
}

void Controller::onDraw(SDL_Surface *screen) {
}

void Controller::onRemove() {
    
}