#pragma once

#include "chunk/ChunkManager.h"

class World
{
    public:
        World();

        void render();

    private:
        ChunkManager m_chunkManager;
};