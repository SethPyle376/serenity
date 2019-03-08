#pragma once

#include "Engine/ResourceManager/ResourceManager.h"
#include "Engine/World/EntityManager.h"
#include "Engine/World/ComponentManager.h"
#include "Engine/World/ServiceManager.h"

#include "Engine/World/Components/TestComponent.h"

#include "Engine/World/Services/TestService.h"

class Application {
private:
    ResourceManager *resourceManager;
    EntityManager *entityManager;
    ComponentManager *componentManager;
    ServiceManager *serviceManager;

    TestService *testService;
    

public:
    Application() {
        resourceManager = new ResourceManager();
        entityManager = new EntityManager();
        componentManager = new ComponentManager();
        serviceManager = new ServiceManager(componentManager);

        Component component;
        component.setId(69);

        TestComponent testComponent;
        testComponent.setId(420);

        TestComponent testComponentTwo;
        testComponentTwo.setId(421);

        componentManager->insertComponent(&component);
        componentManager->insertComponent(&testComponent);
        componentManager->insertComponent(&testComponentTwo);

        Service service;
        serviceManager->addService(service);

        TestService testService;
        serviceManager->addService(testService);

        serviceManager->process();

        return;
    }

    ~Application() {
        delete serviceManager;
        delete componentManager;
        delete entityManager;
        delete resourceManager;
    }
};