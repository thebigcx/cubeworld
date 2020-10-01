#pragma once

#include "chunk/ChunkManager.h"

class World
{
    public:
        World();

        void render();

        Chunk& getChunk(int x, int z);

        void addChunkToUpdateList(int x, int z);

        void update();

    private:
        ChunkManager m_chunkManager;
};