#pragma once

#include <array>

#include "../block/BlockType.h"
#include "../../Mesh.h"
#include "../../util/math/Vector2.h"

constexpr int CHUNK_WIDTH = 16;
constexpr int CHUNK_HEIGHT = 64;

constexpr unsigned int CHUNK_BLOCK_COUNT = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT;

class Chunk
{
    public:
        Chunk(Vector2i p_position);

        void render();

        static int getIndex(int x, int y, int z);

        BlockType getBlock(int x, int y, int z);
        
        std::array<BlockType, CHUNK_BLOCK_COUNT> getBlocks();

        void setBlock(Vector3i pos, BlockType type);

        Vector2i getPosition()
        {
            return m_position;
        }
        
        void update();

        friend class ChunkMeshBuilder;

    private:
        std::array<BlockType, CHUNK_BLOCK_COUNT> m_blocks;
        
        Vector2i m_position;

        Mesh m_mesh;
};