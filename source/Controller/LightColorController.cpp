#include <Hue/Light.h>
#include <Controller/LightColorController.h>
#include <Controller/LightListController.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <Screen.h>

LightColorController::LightColorController(Light * light)
{
    this->light = light;
    this->colorPicker = new ColorPicker(0, 0, BOTTOMSCREEN_WIDTH, SCREEN_HEIGHT);
}

void LightColorController::onCreate(App * app) {
    
}

bool LightColorController::onEvent(SDL_Event * event) {
    this->colorPicker->handleEvent(event);
    switch(event->type) {
        case SDL_KEYDOWN:
            if(event->key.keysym.sym == SDLK_b) {
                App::getInstance()->startController(new LightListController());
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if(this->colorPicker->isClicked(&event->button)) {
                Uint8 r;
                Uint8 g;
                Uint8 b;
                this->colorPicker->getColor(&r, &g, &b);

                printf("R: %d, G: %d, B: %d\n", r, g, b);
            }
            break;
    }
    return false;
}

void LightColorController::onDraw(SDL_Surface *screen) {
    this->colorPicker->draw(screen);
}

void LightColorController::onRemove() {
    
}

