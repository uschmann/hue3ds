#include <Hue/State.h>
#include <cJson.h>

State * State::fromJson(cJSON * json) {
    
    State * state = new State();
    //state->on = cJSON_IsTrue(cJSON_GetObjectItem(json, "on"));

}