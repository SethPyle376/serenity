#pragma once

#include <iostream>

#include "Engine/World/Service.h"
#include "Engine/World/EventManager.h"

#include "Engine/World/Nodes/TestReceiverNode.h"

class TestReceiverService : public Service {
private:

public:
    TestReceiverService() {
        nodeType = typeid(TestReceiverNode).name();
    }

    virtual void process(Node *node) {
        TestReceiverNode *receiverNode = (TestReceiverNode*)node;
        std::vector<Event> events = EventManager::getEvents("test", receiverNode->getId());
        for (int i = 0; i < events.size(); i++) {
            std::cout << "NODE ID: " << node->getId() << " RECEIVED EVENT ID: " << events[i].id << " FROM NODE ID: " 
                                    << events[i].emitter->getId() << " OF TYPE " 
                                    << events[i].type << std::endl;
        }
    }
};