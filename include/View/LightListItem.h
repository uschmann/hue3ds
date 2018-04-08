

#ifndef LightListItem__h
#define LightListItem__h

#include "View.h"
#include <Hue/Light.h>

class LightListItem: public View {
    public:
        LightListItem(Light * light, int x, int y, int width, int height);
        void draw(SDL_Surface * screen);
        bool handleEvent(SDL_Event * event);
    protected:
        Light * light;
};

#endif