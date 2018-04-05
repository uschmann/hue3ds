#include <3ds.h>

#ifndef HttpClient__h
#define HttpClient__h

class HttpClient {
    public:
        char * get(const char *url);
        char * put(const char *url, const char* data);
    protected:
        char * downloadRepsponse(httpcContext *context);
};

#endif