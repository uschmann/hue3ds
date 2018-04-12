#ifndef LIGHT_COLOR_CONTROLLER__H
#define LIGHT_COLOR_CONTROLLER__H

#include <Controller/Controller.h>
#include <Hue/Light.h>
#include <View/LightListItem.h>
#include <vector>
#include <View/ColorPicker.h>

using namespace std;

class LightColorController: public Controller {
    public:
        LightColorController(Light * ligth);
        void onCreate(App * app);
        bool onEvent(SDL_Event * event);
        void onDraw(SDL_Surface *screen);
        void onRemove();
    protected:
        Light * light;
        ColorPicker * colorPicker;
};

#endif