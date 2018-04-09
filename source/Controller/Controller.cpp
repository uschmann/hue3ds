#include <stdio.h>
#include <Controller/Controller.h>

void Controller::onCreate(App * app) {
    this->app = app;
}

bool Controller::onEvent(SDL_Event * event) {
    return false;
}

void Controller::onDraw(SDL_Surface *screen) {
}

void Controller::onRemove() {
    
}