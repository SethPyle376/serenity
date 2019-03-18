#pragma once

#include "Engine/World/Service.h"

#include "Engine/World/ComponentManager.h"

#include "Engine/World/Components/Chunk.h"
#include "Engine/World/Components/MapComponent.h"

class MapGenService : public Service {
private:
    ComponentManager *componentManager;

    void generateMap(MapComponent *map) {
        if (map->init)
            return;
        map->mapChunks.resize(MAP_SIZE);
        for (int i = 0; i < MAP_SIZE; i++) {
            map->mapChunks[i].resize(MAP_SIZE);
            for (int j = 0; j < MAP_SIZE; j++) {
                Chunk *newChunk = new Chunk();
                componentManager->registerComponent(newChunk);
                map->mapChunks[i][j] = newChunk;
            }
        }
        map->init = true;
    }

public:
    MapGenService(ComponentManager *componentManager) {
        componentType = "map";
        this->componentManager = componentManager;
    }

    virtual void process(Component *component) {
        generateMap(((MapComponent*)component));
    }
};