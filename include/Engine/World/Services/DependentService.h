#pragma once

#include "Engine/World/Service.h"
#include "Engine/World/Components/DependentComponent.h"

class DependentService : public Service {
public:
    DependentService() {
        componentType = "dependent";
    }

    virtual void process(Component *component) {
        std::cout << "DEPENDENT COMPONENT: " << ((DependentComponent*)component)->getValue() << std::endl;
    }
};