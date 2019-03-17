#pragma once

#include "Component.h"

class Entity {
private:
    int id;
    std::map<std::string, Component*> components;
public:
    Entity(int id) {
        this->id = id;
    }

    bool hasComponent(std::string type) {
        return components[type] != nullptr;
    }

    void addComponent(Component *component) {
        if (!hasComponent(component->getType())) {
            components[component->getType()] = component;
        }
    }

    void removeComponent(Component *component) {
        if (!hasComponent(component->getType())) {
            components[component->getType()] = nullptr;
        } 
    }

    Component* getComponent(std::string type) {
        return components[type];
    }
};