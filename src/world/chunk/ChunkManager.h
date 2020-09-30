#pragma once

#include <vector>

#include "Chunk.h"

class World;

class ChunkManager
{
    public:
        ChunkManager(World& p_world);

        std::vector<Chunk> getChunks()
        {
            return m_chunks;
        }

    private:
        std::vector<Chunk> m_chunks;

        World* m_world;
};