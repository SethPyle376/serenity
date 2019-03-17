#pragma once

#include <string>

class Component {
friend class ComponentManager;
protected:
    int id;
    int entityId;
    std::string type;
public:
    Component() {};
    Component(int entityId) {
        this->entityId = entityId;
        type = "default";
        id = -1;
    };

    int getId() {
        return id;
    }

    int getEntityId() {
        return entityId;
    }

    std::string getType() {
        return type;
    }
    
    virtual ~Component() {};
};