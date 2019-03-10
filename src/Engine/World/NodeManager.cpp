#include "Engine/World/NodeManager.h"

void NodeManager::create(int entityId, std::string type) {
    Node *newNode;
    Entity *entity = entityManager->getById(entityId);

    if (type == "test") {
        newNode = new TestNode();
    } else {
        std::runtime_error("ERROR: FAILED TO CREATE NODE OF TYPE " + type);
        return;
    }
    std::string typeName = typeid(*newNode).name();
    for (int i = 0; i < entity->nodes.size(); i++) {
        if (typeid(*(entity->nodes[i])).name() == typeName) {
            std::runtime_error("ERROR: ENTITY ALREADY CONTAINS NODE OF TYPE " + type);
            return;
        }
    }
    newNode->create(entity);
    nodes[typeid(*newNode).name()].push_back(newNode);
}