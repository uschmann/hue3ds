#include <Hue/Hue.h>
#include <HttpClient/HttpClient.h>
#include <HttpClient/HttpResponse.h>
#include <cJson.h>
#include <stdio.h>

Hue::Hue() {
    mHttpClient = new HttpClient();
    ip = NULL;
}

void Hue::setUser(char * user) {
    this->user = user;
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

    cJSON *json = cJSON_Parse(response->data);
    cJSON *obj = cJSON_GetArrayItem(json, 0);
    if(cJSON_HasObjectItem(obj, "error")) {
        delete response;
        cJSON_free(json);
        return NULL;
    }

    cJSON *success = cJSON_GetObjectItem(obj, "success");
    cJSON *username = cJSON_GetObjectItem(success, "username");
    char * user = cJSON_GetStringValue(username);
    
    delete response;
    cJSON_free(json);

    return user;
}

