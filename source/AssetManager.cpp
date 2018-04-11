#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <AssetManager.h>
#include <stdio.h>

void AssetManager::init() {
    this->colorPicker = this->loadImage("romfs:/colorpicker.bmp");
}

SDL_Surface * AssetManager::loadImage(char *filename) {
    printf("loading: %s\n", filename);
    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    // let's load dat BMP
    loadedImage = SDL_LoadBMP(filename);
    
    if( loadedImage != NULL ) {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat(loadedImage);
        
        //Free the old image
        SDL_FreeSurface(loadedImage);
    }

    //Return the optimized image
    return optimizedImage;
}