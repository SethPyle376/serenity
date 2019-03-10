#pragma once

#include <vector>

#include "Entity.h"

class Entity;

class Node {
public:
    virtual void create(Entity *entity){};
};