#ifndef LIGHT_LIST_CONTROLLER__H
#define LIGHT_LIST_CONTROLLER__H

#include <Controller/Controller.h>
#include <Hue/Light.h>
#include <View/LightListItem.h>
#include <vector>


using namespace std;

class LightListController: public Controller {
    public:
        void onCreate(App * app);
        void onEvent(SDL_Event * event);
        void onDraw(SDL_Surface *screen);
        void onRemove();
    protected:
        vector<Light> * lights;
        vector<LightListItem> * lightListItems;
};

#endif