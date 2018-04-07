#include <Hue/State.h>
#include <cJson.h>

State * State::fromJson(cJSON * json) {
    
    State * state = new State();
    state->on = cJSON_IsTrue(cJSON_GetObjectItem(json, "on"));
    state->bri = cJSON_GetObjectItem(json, "bri")->valueint;
    state->sat = cJSON_GetObjectItem(json, "sat")->valueint;
    state->hue = cJSON_GetObjectItem(json, "hue")->valueint;
    state->ct = cJSON_HasObjectItem(json, "ct") ? cJSON_GetObjectItem(json, "ct")->valueint : -1;
    state->reachable = cJSON_IsTrue(cJSON_GetObjectItem(json, "reachable"));
    state->colormode = cJSON_GetObjectItem(json, "colormode")->valuestring;

    cJSON * xy = cJSON_GetObjectItem(json, "xy");
    if(cJSON_IsArray(xy)) {
        state->colorX = cJSON_GetArrayItem(xy, 0)->valuedouble;
        state->colorY = cJSON_GetArrayItem(xy, 1)->valuedouble;
    }

    return state;
}