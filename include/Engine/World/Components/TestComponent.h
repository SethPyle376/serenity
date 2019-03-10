#pragma once

#include "Engine/World/Component.h"

class TestComponent : public Component {
public:
    ~TestComponent() {};
    int getId() {
        return 17;
    }
};