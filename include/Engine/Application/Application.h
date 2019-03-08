#pragma once

#include "Engine/ResourceManager/ResourceManager.h"
#include "Engine/World/EntityManager.h"
#include "Engine/World/ComponentManager.h"

#include "Engine/World/Components/TestComponent.h"

class Application {
private:
    ResourceManager *resourceManager;
    EntityManager *entityManager;
    ComponentManager *componentManager;
    

public:
    Application() {
        resourceManager = new ResourceManager();
        entityManager = new EntityManager();
        componentManager = new ComponentManager();

        Component component;
        component.setId(69);

        TestComponent testComponent;
        testComponent.setId(420);

        componentManager->insertComponent(&component);
        componentManager->insertComponent(&testComponent);
        return;
    }

    ~Application() {
        delete componentManager;
        delete entityManager;
        delete resourceManager;
    }
};