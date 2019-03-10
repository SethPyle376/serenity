#pragma once

#include <string>

#include "ServiceManager.h"
#include "Node.h"

class Service {
friend class ServiceManager;
protected:
    std::string nodeType;
public:
    Service(){
        nodeType = typeid(Node).name();
    };

    virtual void process(Node *node) {
        std::cout << "PROCESSING NODE" << std::endl;
    }
};