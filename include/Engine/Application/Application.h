#pragma once

#include "Engine/ResourceManager/ResourceManager.h"
#include "Engine/World/EntityManager.h"
#include "Engine/World/ServiceManager.h"

#include "Engine/World/Services/TestService.h"

class Application {
private:
    ResourceManager *resourceManager;
    EntityManager *entityManager;
    NodeManager *nodeManager;
    ServiceManager *serviceManager;
    TestService *testService;
    

public:
    Application() {
        resourceManager = new ResourceManager();
        entityManager = new EntityManager();
        nodeManager = new NodeManager(entityManager);
        serviceManager = new ServiceManager(nodeManager);

        int entity = entityManager->createEntity();

        nodeManager->create(entity, "test");

        TestService *testService = new TestService();
        serviceManager->addService(testService);

        serviceManager->process();

        return;
    }

    ~Application() {
        delete serviceManager;
        delete nodeManager;
        delete entityManager;
        delete resourceManager;
    }
};