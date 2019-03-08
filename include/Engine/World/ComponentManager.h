#pragma once

#include <map>
#include <typeinfo>
#include <vector>

#include "Component.h"

class ComponentManager {
private:
    std::map<std::string, std::vector<Component*>> componentList;

public:
    ComponentManager();
    void insertComponent(Component *component);
};