#ifndef Light__h
#define Light__h

#include <Hue/state.h>
#include <cJson.h>

class Light {
    public: 
        char * id;
        char * name;
        char * type;
        char * modelid;
        char * swversion;
        char * productid;
        char * archetype;
        State * state;

        static Light * fromJson(cJSON * json);

        void print();
};

#endif