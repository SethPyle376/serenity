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

        for (int i = 0; i < 5; i++) {
            entityManager->createEntity();
        }
    }

    ~Application() {
        delete entityManager;
        delete resourceManager;
    }
};