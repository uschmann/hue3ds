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
    
    cJSON * config = cJSON_GetObjectItem(json, "config");
    light->archetype = cJSON_GetObjectItem(config, "archetype")->valuestring;

    light->state = State::fromJson(cJSON_GetObjectItem(json, "state"));
    return light;
}

void Light::print() {
    printf("Id: %s\n", this->id);
	printf("Name: %s\n", this->name);
	printf("Type: %s\n", this->type);
    printf("Archetxpe: %s\n", this->archetype);
	printf("ModelId: %s\n", this->modelid);
	printf("swversion: %s\n", this->swversion);
    
    printf("State: \n");
    printf("  on: %d\n", this->state->on);
    printf("  hue: %i\n", this->state->hue);
    printf("  sat: %i\n", this->state->sat);
    printf("  bri: %i\n", this->state->bri);
    printf("  x: %f\n", this->state->colorX);
    printf("  y: %f\n", this->state->colorY);
}