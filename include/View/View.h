
#ifndef View__h
#define View__h

#include <SDL/SDL.h>

class View {
    public:
        View(int x, int y, int width, int height);
        void draw(SDL_Surface * screen);
        bool handleEvent(SDL_Event * event);
    protected:
        int x;
        int y;
        int width;
        int height;
};

#endif