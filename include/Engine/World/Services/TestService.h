#pragma once

#include <iostream>

#include "Engine/World/Service.h"
#include "Engine/World/Nodes/TestNode.h"

class TestService : public Service {
public:
    TestService() {
        nodeType = typeid(TestNode).name();
    }

    virtual void process(Node *node) {
        std::cout << "Processing test node: " << ((TestNode*)node)->getComponentData() << std::endl;
    }
};