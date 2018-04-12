#include <View/ColorPicker.h>
#include <SDL/SDL.h>
#include <App.h>
#include <stdio.h>
#include <SdlGfx/SDL_gfxPrimitives.h>

const int RADIUS = 20;

ColorPicker::ColorPicker(int x, int y, int width, int height) 
:View(x, y, width, height) 
{
    this->isMoving = false;
    this->background = App::getInstance()->assetManager->colorPicker;
}

void ColorPicker::draw(SDL_Surface * screen) {
    SDL_Rect offset;
    offset.x = this->x;
    offset.y = this->y;
    SDL_BlitSurface(this->background, NULL, screen, &offset);

    if(this->isMoving) {
        filledCircleRGBA(screen, this->lastX, this->lastY + 2, RADIUS, 0, 0, 0, 100);
        filledCircleRGBA(screen, this->lastX, this->lastY, RADIUS, 255, 255, 255, 255);
        filledCircleRGBA(screen, this->lastX, this->lastY, RADIUS - 2, this->r, this->g, this->b, 255);
    }
}

bool ColorPicker::handleEvent(SDL_Event * event) {
    Uint8 *p = 0;
     switch(event->type) {
        case SDL_MOUSEBUTTONDOWN:
            this->isMoving = true;
            this->lastX = event->button.x;
            this->lastY = event->button.y;
            SDL_LockSurface(this->background);
            p = (Uint8 *)((Uint8 *)(this->background->pixels) + event->button.y * this->background->pitch + event->button.x * 3);
            this->r = p[2];
            this->g = p[1];
            this->b = p[0];
            SDL_UnlockSurface(this->background);
            break;
        case SDL_MOUSEMOTION:
            this->lastX = event->motion.x;
            this->lastY = event->motion.y;
            SDL_LockSurface(this->background);
            p = (Uint8 *)((Uint8 *)(this->background->pixels) + event->motion.y * this->background->pitch + event->motion.x * 3);
            this->r = p[2];
            this->g = p[1];
            this->b = p[0];
            SDL_UnlockSurface(this->background);
            break;
        case SDL_MOUSEBUTTONUP:
            this->isMoving = false;
            this->lastX = event->button.x;
            this->lastY = event->button.y;
            SDL_LockSurface(this->background);
            p = (Uint8 *)((Uint8 *)(this->background->pixels) + event->button.y * this->background->pitch + event->button.x * 3);
            this->r = p[2];
            this->g = p[1];
            this->b = p[0];
            SDL_UnlockSurface(this->background);
            break;
    }
    return false;
}

void ColorPicker::getColor(Uint8 * r, Uint8 * g, Uint8 * b)
{
    *r = this->r;
    *g = this->g;
    *b = this->b;
}