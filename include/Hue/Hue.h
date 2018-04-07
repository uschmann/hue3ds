
#ifndef Hue__H
#define Hue__H

#include <HttpClient/HttpClient.h>
#include <vector>
#include "Light.h"

using namespace std;

class Hue {
    public:
        Hue();
        char * discoverByNupnp();
        void setUser(char * user);
        char * registerUser();

        vector<Light> * getLights();
        bool setOnState(char * id, bool state);
        bool setColorRgb(char *id, double red, double green, double blue);
        bool setColorXy(char *id, double x, double y);
    protected:
        HttpClient *mHttpClient;
        char * ip;
        char * user;
};

#endif