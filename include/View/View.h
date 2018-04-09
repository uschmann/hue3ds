
#ifndef View__h
#define View__h

#include <SDL/SDL.h>

class View {
    public:
        View(int x, int y, int width, int height);
        virtual void draw(SDL_Surface * screen);
        virtual bool handleEvent(SDL_Event * event);
        bool isClicked(SDL_MouseButtonEvent * event);
        void setX(int x);
        void setY(int y);
    protected:
        int x;
        int y;
        int width;
        int height;
};

#endif