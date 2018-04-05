
#ifndef Hue__H
#define Hue__H

#include <HttpClient/HttpClient.h>

class Hue {
    public:
        Hue();
        char * discoverByNupnp();
        void setUser(char * user);
        char * registerUser();
    protected:
        HttpClient *mHttpClient;
        char * ip;
        char * user;
};

#endif