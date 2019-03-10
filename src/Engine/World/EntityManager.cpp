#include "Engine/World/EntityManager.h"

EntityManager::EntityManager() {
    count = 0;
}

int EntityManager::createEntity() {
    Entity *newEntity = new Entity(count);
    entityList.push_back(newEntity);
    return count++;
}

Entity* EntityManager::getById(int id) {
    return entityList[id];
}

int EntityManager::getEntityCount() {
    return count;
}