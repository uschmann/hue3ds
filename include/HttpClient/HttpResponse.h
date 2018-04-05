
#ifndef HttpResponse__h
#define HttpResponse__h

class HttpResponse {
    public:
        HttpResponse(int statuscode, char *data);
        ~HttpResponse();
        int statuscode;
        char *data;
};

#endif