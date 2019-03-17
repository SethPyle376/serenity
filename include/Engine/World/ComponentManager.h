#pragma once

#include <vector>
#include <string>
#include <map>

#include "Engine/World/Entity.h"

#define MAX_COMPONENTS 100000

class ComponentManager {
private:
    int componentCount;
    std::map<std::string, std::map<int, Component*>> componentMap;
public:
    ComponentManager() {
        componentCount = 0;
        return;
    }

    void registerComponent(Component *component) {
        for (int i = 0; i < MAX_COMPONENTS; i++) {
            if (componentMap[component->type][i] == nullptr) {
                component->id = i;
                componentMap[component->type][i] = component;
                componentCount++;
                return;
            }
        }
    }

    void unregisterComponent(Component *component) {
        componentMap[component->type][component->id] = new Component();
    }

    Component* getComponent(std::string type, int id) {
        if (componentMap[type][id]->id == -1) {
            return nullptr;
        } else {
            return componentMap[type][id];
        }
    }

    std::map<int, Component*> getByType(std::string type) {
        return componentMap[type];
    }
};