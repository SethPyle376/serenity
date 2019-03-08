#pragma once

#include <string>

#include "ServiceManager.h"
#include "Component.h"

class Service {
friend class ServiceManager;
protected:
    std::string componentType;
public:
    Service(){
        componentType = typeid(Component).name();
    };

    virtual void process(Component *component) {
        std::cout << component->getId() << std::endl;
    }
};