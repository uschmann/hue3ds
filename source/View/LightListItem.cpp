#include <SDL/SDL.h>
#include <View/LightListItem.h>

LightListItem::LightListItem(Light * light, int x, int y, int width, int height) 
: View(x, y, width, height)
{
    
}

void LightListItem::draw(SDL_Surface * screen) {

}

bool LightListItem::handleEvent(SDL_Event * event) {

}