#include <3ds.h>

class HttpClient {
    public:
        char * get(const char *url);
        char * put(const char *url, const char* data);
    protected:
        char * downloadRepsponse(httpcContext *context);
};