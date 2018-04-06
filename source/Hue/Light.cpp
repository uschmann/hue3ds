#include <Hue/Light.h>
#include <cJson.h>
#include <stdio.h>

Light * Light::fromJson(cJSON * json) {
    Light * light = new Light();

    light->id = json->string;
    light->name = cJSON_GetObjectItem(json, "name")->valuestring;
    light->type = cJSON_GetObjectItem(json, "type")->valuestring;
    light->modelid = cJSON_GetObjectItem(json, "modelid")->valuestring;
    light->swversion = cJSON_GetObjectItem(json, "swversion")->valuestring;
    light->state = State::fromJson(cJSON_GetObjectItem(json, "state"));
    return light;
}