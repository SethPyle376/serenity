#pragma once

#include "Engine/World/Component.h"

class TestComponent : public Component {
private:
    int testValue;
public:
    TestComponent(int entityId) {
        this->entityId = entityId;
        type = "test";
        testValue = 69;
    }

    int getValue() {
        return testValue;
    }

};