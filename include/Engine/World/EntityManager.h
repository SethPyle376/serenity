#pragma once

#include <vector>

#include "Entity.h"

class EntityManager {
private:
    int count;
    std::vector<Entity> entityList;

public:
    EntityManager();
    int createEntity();
    int getEntityCount();
};