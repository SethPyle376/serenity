#pragma once

#include "Engine/ResourceManager/ResourceManager.h"
#include "Engine/World/EntityManager.h"
#include "Engine/World/ServiceManager.h"

#include "Engine/World/Services/TestSenderService.h"
#include "Engine/World/Services/TestReceiverService.h"

class Application {
private:
    ResourceManager *resourceManager;
    EntityManager *entityManager;
    NodeManager *nodeManager;
    ServiceManager *serviceManager;
    
public:
    Application() {
        resourceManager = new ResourceManager();
        entityManager = new EntityManager();
        nodeManager = new NodeManager(entityManager);
        serviceManager = new ServiceManager(nodeManager);

        int entity = entityManager->createEntity();

        int receiver = nodeManager->create(entity, "testReceiver");
        nodeManager->create(entity, "testSender");

        TestSenderService *testSenderService = new TestSenderService(receiver);
        TestReceiverService *testReceiverService = new TestReceiverService(nodeManager);

        serviceManager->addService(testReceiverService);
        serviceManager->addService(testSenderService);

        for (int i = 0; i < 5; i++) {
            serviceManager->process();
        }

        return;
    }

    ~Application() {
        delete serviceManager;
        delete nodeManager;
        delete entityManager;
        delete resourceManager;
    }
};