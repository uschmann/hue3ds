#ifndef App__h
#define App__h

#include <Hue/Hue.h>
#include <SDL/SDL.h>
#include <AssetManager.h>

class Controller;

class App {
    public:
        Hue * hue;
        AssetManager * assetManager;
        static App *getInstance();
        void init();
        void startController(Controller * controller);
        void run();
    protected:
        App();
        static App * INSTANCE; 
        SDL_Surface *screen;
        bool isRunning;
        Uint32 lastMouseDown;
        Controller * controller;
};

#endif 