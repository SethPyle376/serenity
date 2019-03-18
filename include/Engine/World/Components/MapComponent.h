#pragma once

#include <vector>

#include "Engine/World/Component.h"
#include "Engine/World/Components/Chunk.h"

#define MAP_SIZE 32

class MapComponent : public Component {
friend class MapGenService;
private:
    std::vector<std::vector<Chunk*>> mapChunks;
    bool init;
public:
    MapComponent() {
        init = false;
        type = "map";
    }
};