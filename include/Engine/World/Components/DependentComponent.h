#pragma once

#include "Engine/World/EntityManager.h"
#include "Engine/World/Components/TestComponent.h"

class DependentComponent : public Component {
friend class DependentService;
private:
    Component *testComponent;

public:
    DependentComponent(int entityId, EntityManager *entityManager) {
        this->entityId = entityId;
        TestComponent *testComponent = new TestComponent(entityId);
        entityManager->addComponent(testComponent);
        this->testComponent = entityManager->getEntity(entityId)->getComponent(testComponent->getType());

        type = "dependent";
    }

    int getValue() {
        return ((TestComponent*)testComponent)->getValue();
    }
};