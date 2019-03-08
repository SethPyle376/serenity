#pragma once

#include <vector>
#include <string>

#include "Service.h"

class ServiceManager {
private:

    ComponentManager *componentManager;

    std::vector<Service> serviceList;
public:
    ServiceManager(ComponentManager *componentManager) {
        this->componentManager = componentManager;
    };

    void addService(Service service) {
        serviceList.push_back(service);
    }

    void process() {
        for (int i = 0; i < serviceList.size(); i++) {
            std::vector<Component*> components = componentManager->getComponents(serviceList[i].componentType);
            for (int j = 0; j < components.size(); j++) {
                serviceList[i].process(components[j]);
            }
        }
    }
};