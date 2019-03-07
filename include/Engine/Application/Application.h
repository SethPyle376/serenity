#pragma once

#include "Engine/ResourceManager/ResourceManager.h"
#include "Engine/World/EntityManager.h"

class Application {
private:
    ResourceManager *resourceManager;
    EntityManager *entityManager;

public:
    Application() {
        resourceManager = new ResourceManager();
        entityManager = new EntityManager();
    }

    ~Application() {
        delete entityManager;
        delete resourceManager;
    }
};