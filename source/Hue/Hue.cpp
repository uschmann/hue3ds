#include <Hue/Hue.h>
#include <HttpClient/HttpClient.h>
#include <HttpClient/HttpResponse.h>
#include <cJson.h>
#include <stdio.h>

Hue::Hue() {
    mHttpClient = new HttpClient();
    ip = NULL;
}

char * Hue::discoverByNupnp() {
    HttpResponse * response = mHttpClient->get("https://www.meethue.com/api/nupnp");

    cJSON *json = cJSON_Parse(response->data);
    if(cJSON_GetArraySize(json) == 0) {
        return NULL;
    }

    cJSON *bridge = cJSON_GetArrayItem(json, 0);
    cJSON *internalipaddress = cJSON_GetObjectItem(bridge, "internalipaddress");
    this->ip = cJSON_GetStringValue(internalipaddress);
    
    delete response;
    cJSON_free(json);

    return this->ip;
}

char * Hue::registerUser() {
    char url[50];
    sprintf(url, "http://%s/api", this->ip);
    
    HttpResponse * response = mHttpClient->post(url, "{\"devicetype\":\"hue3ds#3ds\"}");

    return response->data;
}