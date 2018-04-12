#include <View/ColorPicker.h>
#include <SDL/SDL.h>
#include <App.h>
#include <stdio.h>

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
}

bool ColorPicker::handleEvent(SDL_Event * event) {
     switch(event->type) {
        case SDL_MOUSEBUTTONUP:
            SDL_LockSurface(this->background);
            
            Uint8 *p = (Uint8 *)(this->background->pixels + event->button.y * this->background->pitch + event->button.x * 3);
            this->r = p[2];
            this->g = p[1];
            this->b = p[0];
            
            SDL_UnlockSurface(this->background);
            break;
    }
}

void ColorPicker::getColor(Uint8 * r, Uint8 * g, Uint8 * b)
{
    *r = this->r;
    *g = this->g;
    *b = this->b;
}