#include <stdio.h>

#include <Controller/LightListController.h>

void LightListController::onCreate(App * app) {
    Controller::onCreate(app);

    this->lights = app->hue->getLights();
    printf("Lights: %d\n", lights->size());
}

void LightListController::onEvent(SDL_Event * event) {
    printf("On Event LightListController\n");
}

void LightListController::onDraw(SDL_Surface *screen) {
    printf("On Draw LightListController\n");
}

void LightListController::onRemove() {
    printf("On Draw onRemove\n");
}
