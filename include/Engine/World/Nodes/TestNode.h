#pragma once

#include "Engine/World/Node.h"

#include "Engine/World/Components/TestComponent.h"

class TestNode : public Node {
private:
    TestComponent *testComponent;
public:
    virtual void create(Entity *entity) {
        testComponent = nullptr;
        std::vector<Component*> entityComponents = *entity->getComponents();
        for (int i = 0; i < entityComponents.size(); i++) {
            if (dynamic_cast<TestComponent*>(entityComponents[i]) != nullptr) {
                testComponent = (TestComponent*)entityComponents[i];
                break;
            }
            if (i == entityComponents.size() - 1) {
                testComponent = new TestComponent();
                entity->getComponents()->push_back(testComponent);
            }
        }
        entity->getNodes()->push_back(this);
    }
    
    int getComponentData() {
        return testComponent->getId();
    }
};
