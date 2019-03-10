#pragma once

#include "Node.h"
#include "Component.h"

class Entity {
friend class NodeManager;
private:
    int id;
    std::vector<Component*> components;
    std::vector<Node*> nodes;
public:
    Entity(int id);

    std::vector<Component*>* getComponents() {
        return &components;
    }

    std::vector<Node*>* getNodes() {
        return &nodes;
    }
};