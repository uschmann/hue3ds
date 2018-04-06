

#ifndef State__h
#define State__h

#include <cJSON.h>

class State {
    public:
        bool on;
        static State * fromJson(cJSON * json);
};

#endif