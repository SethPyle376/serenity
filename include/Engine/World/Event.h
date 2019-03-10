#pragma once

#include <string>

#include "Node.h"

struct Event {
    int id;
    int nodeId;
    std::string type;
    Node *emitter;
};