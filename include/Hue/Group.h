#ifndef Group__H
#define Group__H

#include <cJson.h>

class Group {
    public:
        char * id;
        char * name;
        static Group * fromJson(cJSON * json);
};

#endif