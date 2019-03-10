#pragma once

#include <iostream>

#include "Engine/World/Service.h"
#include "Engine/World/Nodes/TestSenderNode.h"
#include "Engine/World/EventManager.h"

class TestSenderService : public Service {
private:
    int targetNode;
public:
    TestSenderService(int targetNode) {
        nodeType = typeid(TestSenderNode).name();
        this->targetNode = targetNode;
    }

    virtual void process(Node *node) {
        Event event;
        event.emitterId = node->getId();
        event.type = "test";
        event.targetId = targetNode;
        EventManager::dispatch(event);
        std::cout << "NODE ID: " << node->getId() << " DISPATCHING TO NODE " << targetNode << std::endl;
    }
};