#pragma once

#include <vector>

#include "Entity.h"

#define MAX_ENTITIES 100000

class EntityManager {
private:
    int count;
    std::vector<Entity*> entityList;
public:
    int createEntity() {
        count++;
        for (int i = 0; i < entityList.capacity(); i++) {
            if (entityList[i] == nullptr) {
                entityList[i] = new Entity(i);
                return i;
            }
        }
        entityList.push_back(new Entity(entityList.capacity() - 1));
        return entityList.capacity() - 1;
    }

    void addComponent(Component *component) {
        entityList[component->getEntityId()]->addComponent(component);
    }

    void deleteEntity(int entity) {
        entityList[entity] = nullptr;
        count--;
    }

    int getEntityCount() {
        return count;
    }

    Entity* getEntity(int id) {
        return entityList[id];
    }
};