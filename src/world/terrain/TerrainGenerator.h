#pragma once

#include "../chunk/Chunk.h"

#include <array>

typedef std::array<BlockType, CHUNK_BLOCK_COUNT> BlockMap;

struct TerrainGenerator
{
    private:

        

    public:

        static BlockMap generateChunk(int xPos, int zPos);

};