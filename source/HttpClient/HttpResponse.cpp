#include <stdlib.h>
#include "../include/HttpClient/HttpResponse.h"

HttpResponse::HttpResponse(int statuscode, char *data) {
    this->statuscode = statuscode;
    this->data = data;
}

HttpResponse::~HttpResponse() {
    free(this->data);
}