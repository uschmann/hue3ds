#include <Hue/Light.h>
#include <Controller/LightColorController.h>
#include <Controller/LightListController.h>
#include <stdio.h>
#include <SDL/SDL.h>

LightColorController::LightColorController(Light * light)
{
    this->light = light;
}

void LightColorController::onCreate(App * app) {
    
}

Uint32 getpixel(SDL_Surface *surface, int x, int y, Uint8 * r, Uint8 * g, Uint8 * b)
{
    SDL_LockSurface(surface);
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * 3;
    *r = p[2];
    *g = p[1];
    *b = p[0];
    SDL_UnlockSurface(surface);
}

bool LightColorController::onEvent(SDL_Event * event) {
    switch(event->type) {
        case SDL_KEYDOWN:
            if(event->key.keysym.sym == SDLK_b) { // Start
                App::getInstance()->startController(new LightListController());
            }
            break;
        case SDL_MOUSEBUTTONUP:
            SDL_Surface * colorpicker = App::getInstance()->assetManager->colorPicker;
            Uint8 r;
            Uint8 g;
            Uint8 b;

            getpixel(colorpicker, event->button.x, event->button.y, &r, &g, &b);

            App::getInstance()->hue->setColorRgb(this->light->id, r, g, b);

            printf("r: %d, g:%d b%d\n", r, g, b);
            break;
    }
    return false;
}

void LightColorController::onDraw(SDL_Surface *screen) {
    SDL_Rect offset;
    offset.x = 0;
    offset.y = 0;
    SDL_Surface * colorpicker = App::getInstance()->assetManager->colorPicker;
    
    SDL_BlitSurface(colorpicker, NULL, screen, &offset);
}

void LightColorController::onRemove() {
    
}

