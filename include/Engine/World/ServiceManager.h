#pragma once

#include <vector>
#include <string>

#include "Service.h"
#include "ComponentManager.h"
#include "EventManager.h"

class ServiceManager {
private:
    std::vector<Service*> serviceList;
    ComponentManager *componentManager;
    EventManager *eventManager;
public:
    ServiceManager(ComponentManager *componentManager, EventManager *eventManager) {
        this->componentManager = componentManager;
        this->eventManager = eventManager;
    }

    void addService(Service *service) {
        serviceList.push_back(service);
    }

    void process() {
        for (int i = 0; i < serviceList.size(); i++) {
            std::map<int, Component*> components = componentManager->getByType(serviceList[i]->componentType);
            for (auto componentPair : components) {
                serviceList[i]->process(componentPair.second);
                std::queue eventQueue = eventManager->getEvents(serviceList[i]->componentType, componentPair.second->getId());
                while (!eventQueue.empty()) {
                    serviceList[i]->processEvent(componentPair.second, eventQueue.front());
                    eventQueue.pop();
                }
            }
        }
    }
};