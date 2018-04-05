#include <3ds.h>
#include "HttpResponse.h"

#ifndef HttpClient__h
#define HttpClient__h

class HttpClient {
    public:
        HttpResponse * get(const char *url);
        HttpResponse * post(const char *url, const char* data);
        HttpResponse * put(const char *url, const char* data);
    protected:
        char * downloadRepsponse(httpcContext *context);
};

#endif