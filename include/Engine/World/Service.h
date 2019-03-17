#pragma once

#include <iostream>
#include <string>

#include "ServiceManager.h"

class Service {
friend class ServiceManager;
protected:
    std::string componentType;
public:
    Service() {
        componentType = "default";
    }

    virtual void process(Component *component) {
        std::cout << "DEFAULT COMPONENT: " << component->getId() << std::endl;
    }

    virtual void processEvent(Component *component, Event event) {
        std::cout << "PROCESSED EVENT: " << event.id << " DATA: " << event.data << std::endl; 
    }
};