#ifndef App__h
#define App__h

#include <Hue/Hue.h>
#include <SDL/SDL.h>

class Controller;

class App {
    public:
        Hue * hue;
        static App *getInstance();
        void init();
        void startController(Controller * controller);
        void run();
    protected:
        App();
        static App * INSTANCE; 
        SDL_Surface *screen;
        bool isRunning;
        Controller * controller;
};

#endif 