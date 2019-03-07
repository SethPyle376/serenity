#include "Engine/World/EntityManager.h"

EntityManager::EntityManager() {
    //logging
}

int EntityManager::createEntity() {
    count++;
    Entity newEntity(count);
    entityList.push_back(newEntity);
    return count;
}

int EntityManager::getEntityCount() {
    return count;
}