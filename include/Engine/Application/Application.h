#pragma once

#include "Engine/World/ComponentManager.h"
#include "Engine/World/EntityManager.h"
#include "Engine/World/EventManager.h"
#include "Engine/World/ServiceManager.h"
#include "Engine/ResourceManager/ResourceManager.h"

#include "Engine/World/Components/TestComponent.h"
#include "Engine/World/Services/TestService.h"

#include "Engine/World/Components/DependentComponent.h"
#include "Engine/World/Services/DependentService.h"

class Application {
private:
    ResourceManager *resourceManager;
    ComponentManager *componentManager;
    ServiceManager *serviceManager;
    EventManager *eventManager;
    EntityManager *entityManager;
    
public:
    Application() {
        entityManager = new EntityManager();
        componentManager = new ComponentManager();
        eventManager = new EventManager();
        serviceManager = new ServiceManager(componentManager, eventManager);
        return;
    }

    void process() {
        int testEntity = entityManager->createEntity();

        serviceManager->addService(new Service());
        serviceManager->addService(new TestService());
        serviceManager->addService(new DependentService());
        componentManager->registerComponent(new Component(testEntity));
        componentManager->registerComponent(new Component(testEntity));
        componentManager->registerComponent(new TestComponent(testEntity));
        componentManager->registerComponent(new DependentComponent(testEntity, entityManager));

        for(int i = 0; i < 4; i++) {
            serviceManager->process();
        }
        return;
    }

    ~Application() {

    }
};