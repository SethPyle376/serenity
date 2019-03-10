#pragma once

#include <map>
#include <typeinfo>

#include "Entity.h"

#include "Engine/World/EntityManager.h"
#include "Engine/World/Nodes/TestReceiverNode.h"
#include "Engine/World/Nodes/TestSenderNode.h"

class NodeManager {
friend class Node;
private:
    int count;
    EntityManager *entityManager;
    std::vector<Node*> nodeList;
    std::map<std::string, std::vector<Node*>> nodes;
public:
    NodeManager(EntityManager *entityManager){
        this->entityManager = entityManager;
        count = 0;
    };
    int create(int entityId, std::string type);
    std::vector<Node*> getNodes(std::string type) {
        return nodes[type];
    }
    Node* getById(int id) {
        return nodeList[id];
    }
};