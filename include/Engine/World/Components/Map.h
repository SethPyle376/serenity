#pragma once

#include <vector>

#include "Engine/World/Component.h"
#include "Engine/World/Components/Chunk.h"


class Map : public Component {
private:
    std::vector<std::vector<Chunk*>> mapChunks;
    int mapSize;
public:
    Map(int mapSize) {
        type = "map";
        this->mapSize = mapSize;
        mapChunks.resize(mapSize);
        for (int i = 0; i < mapChunks.size(); i++) {
            mapChunks[i].resize(mapSize);
        }
    }
}