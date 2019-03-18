#include "Engine/World/Component.h"

#define CHUNK_SIZE 32

class Chunk : public Component {
private:
    int chunkSize;
    int **terrainData;
public:
    Chunk() {
        type = "mapchunk";
        terrainData = new int*[CHUNK_SIZE];
        for (int i = 0; i < CHUNK_SIZE; i++) {
            terrainData[i] = new int[CHUNK_SIZE];
            for (int j = 0; j < CHUNK_SIZE; j++) {
                terrainData[i][j] = -1;
            }
        }
    }
};