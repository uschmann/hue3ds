#include <Hue/Group.h>
#include <cJson.h>

Group * Group::fromJson(cJSON * json) {
    Group * group = new Group();

    group->id = json->string;
    group->name = cJSON_GetObjectItem(json, "name")->valuestring;
    return group;
}