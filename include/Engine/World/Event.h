#pragma once

#include <string>

struct Event {
    int id;
    int targetId;
    int emitterId;
    std::string componentType;
    std::string data;
};