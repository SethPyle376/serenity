#pragma once

#include <string>

#include "Node.h"

struct Event {
    int id;
    int targetId;
    std::string type;
    int emitterId;
};