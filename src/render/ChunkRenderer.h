#pragma once

#include "../world/chunk/Chunk.h"

class ChunkRenderer
{
    public:
        ChunkRenderer() {};

        void render(Chunk& p_chunk);
};