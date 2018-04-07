#include <Hue/Hue.h>
#include <Hue/Light.h>
#include <HttpClient/HttpClient.h>
#include <HttpClient/HttpResponse.h>
#include <cJson.h>
#include <stdio.h>

Hue::Hue() {
    mHttpClient = new HttpClient();
    ip = NULL;
    user = NULL;
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

vector<Light> * Hue::getLights() {
    vector<Light> * lights = new vector<Light>;

    char url[100];
    sprintf(url, "http://%s/api/%s/lights", this->ip, this->user);
    HttpResponse * response = mHttpClient->get(url);

    cJSON * json = cJSON_Parse(response->data);
    cJSON * light = NULL;
    cJSON_ArrayForEach(light, json) {
        lights->push_back(*Light::fromJson(light));
    }

    cJSON_free(json);
    delete response;

    return lights;
}

bool Hue::setOnState(char * id, bool state) {
    HttpResponse * response = NULL;
    char url[100];
    sprintf(url, "http://%s/api/%s/lights/%s/state", this->ip, this->user, id);

    if(state) {
        response = mHttpClient->put(url, "{\"on\":true}");
    }
    else {
        response = mHttpClient->put(url, "{\"on\":false}");
    }

    bool success = response->statuscode == 200;
    delete response;

    return success;
}