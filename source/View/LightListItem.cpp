#include <SDL/SDL.h>
#include <SdlGfx/SDL_gfxPrimitives.h>
#include <View/LightListItem.h>
#include <App.h>
#include <stdio.h>
#include <Event.h>
#include <Hue/ColorRgb.h>
#include <Controller/LightColorController.h>

LightListItem::LightListItem(Light * light, int x, int y, int width, int height) 
: View(x, y, width, height)
{
    this->light = light;
    this->color = ColorRgb::fromXy(this->light->state->colorX, this->light->state->colorY, ((float)this->light->state->bri / 254.f)); 
}

void LightListItem::draw(SDL_Surface * screen) {
    bool isOn = this->light->state->on;

    if(isOn) {
        boxRGBA(screen, this->x, this->y, this->x + this->width, this->y + this->height, this->color->r, this->color->g, this->color->b, 254);    
        //boxColor(screen, this->x, this->y, this->x + this->width, this->y + this->height, 0x333333FF);   
    }
    else {
        boxColor(screen, this->x, this->y, this->x + this->width, this->y + this->height, 0x000000FF);    
    }
    circleColor(screen, this->x + this->height / 2 + 10, this->y + this->height / 2, this->height / 2 - 10, 0xFFFFFFFF);
    
    stringColor (screen, this->x + this->height / 2 + 50, this-> y + this->height / 2 - 3, this->light->name, 0xFFFFFFFF);
    hlineColor(screen, this->x, 340, this->y + this->height - 1, 0xFFFFFFFF);   
}

bool LightListItem::handleEvent(SDL_Event * event) {
    switch(event->type)
    {
        case SDL_USEREVENT:
            if(event->user.code == TAP_EVENT && this->isClicked((SDL_MouseButtonEvent*)event->user.data1)) {
                if(((SDL_MouseButtonEvent*)event->user.data1)->x < 100) {
                    this->light->state->on = !this->light->state->on;
                    App::getInstance()->hue->setOnState(this->light->id, this->light->state->on);
                }
                else {
                    App::getInstance()->startController(new LightColorController(this->light));
                }
            }
            break;
    }
    return false;
}