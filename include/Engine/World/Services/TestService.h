#pragma once

#include <iostream>

#include "Engine/World/Service.h"
#include "Engine/World/Components/TestComponent.h"

class TestService : public Service {
public:
    TestService() {
        componentType = typeid(TestComponent).name();
    }

    virtual void process(Component *component) {
        std::cout << component->getId() << " called from child" << std::endl;
    }
};