#pragma once

#include <map>
#include <typeinfo>

#include "Entity.h"

#include "Engine/World/EntityManager.h"
#include "Engine/World/Nodes/TestNode.h"

class NodeManager {
private:
    EntityManager *entityManager;
    std::map<std::string, std::vector<Node*>> nodes;
public:
    NodeManager(EntityManager *entityManager){
        this->entityManager = entityManager;
    };
    void create(int entityId, std::string type);
    std::vector<Node*> getNodes(std::string type) {
        return nodes[type];
    }
};