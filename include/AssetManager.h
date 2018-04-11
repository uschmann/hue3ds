

#ifndef AssetManager__h
#define AssetManager__h

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class AssetManager {
    public: 
        void init();
        SDL_Surface * colorPicker;
    protected:
        SDL_Surface *loadImage(char *filename);


};

#endif