#pragma once

#include "Engine/ResourceManager/ResourceManager.h"

class Application {
    private:
    ResourceManager *resourceManager;

    public:
    Application() {
        resourceManager = new ResourceManager();
    }
};