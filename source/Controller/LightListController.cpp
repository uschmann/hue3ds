#include <stdio.h>
#include <SDL/SDL.h>
#include <Controller/LightListController.h>
#include <SdlGfx/SDL_gfxPrimitives.h>

void LightListController::onCreate(App * app) {
    Controller::onCreate(app);

    this->lights = app->hue->getLights();
    this->lightListItems = new vector<LightListItem *>();
    this->offsetY = 0;
    this->isDragging = false;
    
    for (int i = 0; i < this->lights->size(); i++) {
        Light * light = &this->lights->at(i);
        this->lightListItems->push_back(new LightListItem(light, 0, i * 70, 340, 70));
    }
}

bool LightListController::onEvent(SDL_Event * event) {
    switch(event->type) {
        case SDL_MOUSEMOTION:
            if(this->isDragging) {
                int maxOffset = ((this->lightListItems->size() - 1) * 70);
                this->offsetY += event->motion.yrel;
                
                if(this->offsetY < maxOffset * -1) {
                    this->offsetY = maxOffset * -1;
                }

                if(this->offsetY > 0 ) {
                   this->offsetY = 0;
                }
                
                for (int i = 0; i < this->lightListItems->size(); i++) {
                    this->lightListItems->at(i)->setY((70 *i) + this->offsetY);
                }
            }
            else {
                this->isDragging = true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            this->isDragging = false;
            break;
    }

    for (int i = 0; i < this->lightListItems->size(); i++) {
        this->lightListItems->at(i)->handleEvent(event);
    }

    return false;
}

void LightListController::onDraw(SDL_Surface *screen) {
    boxColor(screen, 0, 0, 340, 240, 0x000000FF);    
    for (int i = 0; i < this->lightListItems->size(); i++) {
        this->lightListItems->at(i)->draw(screen);
    }
}

void LightListController::onRemove() {
    printf("On Draw onRemove\n");
}
