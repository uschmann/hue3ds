

#ifndef ColorPicker__h
#define ColorPicker__h

#include <SDL/SDL.h>
#include "View.h"


class ColorPicker: public View {
    public:
        ColorPicker(int x, int y, int width, int height);
        void draw(SDL_Surface * screen);
        bool handleEvent(SDL_Event * event);
        void getColor(Uint8 * r, Uint8 * g, Uint8 * b);
    protected:
        bool isMoving;
        Uint8 r;
        Uint8 g;
        Uint8 b;
        SDL_Surface * background;
        int lastX;
        int lastY;
};

#endif