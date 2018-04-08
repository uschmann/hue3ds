
#include <View/View.h>
#include <SdlGfx/SDL_gfxPrimitives.h>
#include <stdio.h>

View::View(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width; 
    this->height = height;
}

void View::draw(SDL_Surface * screen) {
    roundedBoxColor(screen, 
        this->x, 
        this->y, 
        this->width, 
        this->height, 
        50, 
        0x123456FF
    );
}

bool View::handleEvent(SDL_Event * event) {
    return false;
}

bool View::isClicked(SDL_MouseButtonEvent * event) {
    return event->x >= this-> x && event->x <= this->x + this->width &&
        event->y >= this->y && event->y <= this->y + this->height;
}