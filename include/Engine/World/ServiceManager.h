#pragma once

#include <vector>
#include <string>

#include "Service.h"
#include "NodeManager.h"

class ServiceManager {
private:
    NodeManager *nodeManager;
    std::vector<Service*> serviceList;
public:
    ServiceManager(NodeManager *nodeManager) {
        this->nodeManager = nodeManager;
    };

    void addService(Service *service) {
        serviceList.push_back(service);
    }

    void process() {
        for (int i = 0; i < serviceList.size(); i++) {
            std::string type = serviceList[i]->nodeType;
            std::vector<Node*> nodes = nodeManager->getNodes(type);
            for (int j = 0; j < nodes.size(); j++) {
                serviceList[i]->process(nodes[j]);
            }
        }
    }
};