#include <stdio.h>

#include <Controller/LightListController.h>

void LightListController::onCreate(App * app) {
    Controller::onCreate(app);

    this->lights = app->hue->getLights();
    this->lightListItems = new vector<LightListItem>();
    printf("Lights: %d\n", this->lights->size());
    for (int i = 0; i < this->lights->size(); i++) {
        Light * light = &this->lights->at(i);
        this->lightListItems->push_back(*new LightListItem(light, 0, i * 70, 340, 70));
    }
}

void LightListController::onEvent(SDL_Event * event) {
    for (int i = 0; i < this->lightListItems->size(); i++) {
        this->lightListItems->at(i).handleEvent(event);
    }
}

void LightListController::onDraw(SDL_Surface *screen) {
    for (int i = 0; i < this->lightListItems->size(); i++) {
        this->lightListItems->at(i).draw(screen);
    }
}

void LightListController::onRemove() {
    printf("On Draw onRemove\n");
}
