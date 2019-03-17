#pragma once

#include "Engine/World/Service.h"
#include "Engine/World/Components/TestComponent.h"
#include "Engine/World/EventManager.h"

class TestService : public Service {

public:
    TestService() {
        componentType = "test";
    }

    virtual void process(Component *component) {
        std::cout << "TEST COMPONENT VALUE: " << ((TestComponent*)component)->getValue() << std::endl;
        Event event;
        event.componentType = "test";
        event.emitterId = component->getId();
        event.targetId = component->getId();
        event.data = "hello";
        EventManager::dispatch(event);
    }
};