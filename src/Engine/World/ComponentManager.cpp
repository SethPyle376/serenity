#include "Engine/World/ComponentManager.h"

ComponentManager::ComponentManager() {

}

void ComponentManager::insertComponent(Component *component) {
    std::string typeName = typeid(*component).name();
    std::vector<Component*> *componentVector = &componentList[typeName];
    componentVector->push_back(component);
}

std::vector<Component*> ComponentManager::getComponents(std::string type) {
    return componentList[type];
}
