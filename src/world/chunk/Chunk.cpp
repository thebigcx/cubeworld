#include "Chunk.h"

#include "../../texture/TextureAtlas.h"
#include "../block/BlockVertices.h"
#include "../block/BlockManager.h"
#include "../../util/math/Vector3.h"
#include "../terrain/TerrainGenerator.h"
#include "ChunkMeshBuilder.h"

Chunk::Chunk(Vector2i p_position)
: m_position(p_position)
{
    m_blocks = TerrainGenerator::generateChunk(p_position.x, p_position.y);
    m_mesh = ChunkMeshBuilder::buildChunkMesh(*this);
    
    

    m_mesh.setPosition(Vector3f(p_position.x * 16, 0, p_position.y * 16));
}

void Chunk::render()
{
    m_mesh.render();
}

int Chunk::getIndex(int x, int y, int z)
{
    // Do some magic to find the index
    return x + CHUNK_WIDTH * (y + CHUNK_HEIGHT * z);
}

void Chunk::setBlock(Vector3i pos, BlockType type)
{
    int index = getIndex(pos.x, pos.y, pos.z);
    m_blocks[index].setType(type.getId());
}

std::array<BlockType, CHUNK_BLOCK_COUNT> Chunk::getBlocks()
{
    return m_blocks;
}

BlockType Chunk::getBlock(int x, int y, int z)
{
    return m_blocks[getIndex(x, y, z)];
}

void Chunk::update()
{
    m_mesh = ChunkMeshBuilder::buildChunkMesh(*this);
    m_mesh.setPosition(Vector3f(m_position.x * 16, 0, m_position.y * 16));
}