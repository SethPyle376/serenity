#pragma once

#include <vector>

#include "Entity.h"

#define MAX_ENTITIES 100000

class EntityManager {
private:
    int count;
    std::vector<bool> entityList;
public:
    int createEntity() {
        count++;
        for (int i = 0; i < entityList.capacity(); i++) {
            if (!entityList[i]) {
                entityList[i] = true;
                return i;
            }
        }
        entityList.push_back(true);
        return entityList.capacity() - 1;
    }

    void deleteEntity(int entity) {
        entityList[entity] = false;
        count--;
    }

    int getEntityCount() {
        return count;
    }
};