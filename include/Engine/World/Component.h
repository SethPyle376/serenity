#pragma once

class Component {
private:
    int id;

public:
    Component() {};
    virtual ~Component() {};

    void setId(int id) {
        this->id = id;
    }

    int getId() {
        return id;
    }
};