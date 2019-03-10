#pragma once

#include <vector>

#include "Entity.h"

class Entity;

class Node {
private:
    int id;
public:
    void setId(int id) {
        this->id = id;
    }
    int getId() {
        return id;
    }
    virtual void create(Entity *entity){};
};