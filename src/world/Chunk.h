#pragma once

#include <array>

#include "Block.h"
#include "../Mesh.h"
#include "../util/math/Vector2.h"

constexpr int CHUNK_WIDTH = 16;
constexpr int CHUNK_HEIGHT = 256;

constexpr unsigned int CHUNK_BLOCK_COUNT = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT;

class Chunk
{
    public:
        Chunk(Vector2i p_position);

        void render();

    private:
        std::array<Block, CHUNK_BLOCK_COUNT> m_blocks;
        
        Vector2i m_position;

        Mesh m_mesh;
};