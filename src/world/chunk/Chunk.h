#pragma once

#include <array>

#include "../block/BlockType.h"
#include "../../Mesh.h"
#include "../../util/math/Vector2.h"

constexpr int CHUNK_WIDTH = 16;
constexpr int CHUNK_HEIGHT = 64;

constexpr unsigned int CHUNK_BLOCK_COUNT = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT;

class World;

class Chunk
{
    public:
        Chunk(World& p_world, Vector2i p_position);

        void render();

        static int getIndex(int x, int y, int z);

        int getBlock(int x, int y, int z) const;
        
        std::array<BlockType, CHUNK_BLOCK_COUNT> getBlocks();

        void setBlock(Vector3i pos, BlockType type);

        Vector2i getPosition()
        {
            return m_position;
        }
        
        void update();

        friend class ChunkMeshBuilder;
        friend class ChunkRenderer;


    private:
        std::array<BlockType, CHUNK_BLOCK_COUNT> m_blocks;
        
        Vector2i m_position;

        Mesh m_mesh;

        World* m_world;
};