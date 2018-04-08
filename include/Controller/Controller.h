#ifndef Controller__h
#define Controller__h


#include <SDL/SDL.h>
#include <App.h>

class Controller {
    public:
        virtual void onCreate(App * app);
        virtual void onEvent(SDL_Event * event);
        virtual void onDraw(SDL_Surface *screen);
        virtual void onRemove();
    protected:
        App * app;
};

#endif