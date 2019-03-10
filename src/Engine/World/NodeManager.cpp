#include "Engine/World/NodeManager.h"

int NodeManager::create(int entityId, std::string type) {
    Node *newNode;
    Entity *entity = entityManager->getById(entityId);

    if (type == "testReceiver") {
        newNode = new TestReceiverNode();
    } else if (type == "testSender") {
        newNode = new TestSenderNode();
    } else {
        std::runtime_error("ERROR: FAILED TO CREATE NODE OF TYPE " + type);
        return -1;
    }
    std::string typeName = typeid(*newNode).name();
    for (int i = 0; i < entity->nodes.size(); i++) {
        if (typeid(*(entity->nodes[i])).name() == typeName) {
            std::runtime_error("ERROR: ENTITY ALREADY CONTAINS NODE OF TYPE " + type);
            return entity->nodes[i]->getId();
        }
    }
    newNode->create(entity);
    newNode->setId(count);
    nodes[typeid(*newNode).name()].push_back(newNode);
    nodeList.push_back(newNode);
    return count++;
}