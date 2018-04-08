#ifndef Controller__h
#define Controller__h


#include <SDL/SDL.h>
#include <App.h>

class Controller {
    public:
        void onCreate(App * app);
        void onEvent(SDL_Event * event);
        void onDraw(SDL_Surface *screen);
    protected:
        App * app;
};

#endif