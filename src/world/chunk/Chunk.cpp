#include "Chunk.h"

#include "../../texture/TextureAtlas.h"
#include "../block/BlockVertices.h"
#include "../block/BlockManager.h"
#include "../../util/math/Vector3.h"
#include "../terrain/TerrainGenerator.h"
#include "ChunkMeshBuilder.h"
#include "../World.h"
#include "../../util/Timer.h"

Chunk::Chunk(World& p_world, Vector2i p_position, long seed)
: m_position(p_position)
, m_world(&p_world)
{
    m_blocks = TerrainGenerator::generateChunk(p_position.x, p_position.y, seed);
    m_mesh = ChunkMeshBuilder::buildChunkMesh(*this);

    m_mesh.setPosition(Vector3f(p_position.x * 16.f, 0.f, p_position.y * 16.f));
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

int Chunk::getBlock(int x, int y, int z) const
{
    if (x < 0 || x >= CHUNK_WIDTH || z < 0 || z >= CHUNK_WIDTH)
    {
        // Out of bounds
        Vector3i worldPos(x + (m_position.x * CHUNK_WIDTH), y, z + (m_position.y * CHUNK_WIDTH));
        return m_world->getBlock(worldPos.x, worldPos.y, worldPos.z);
    }

    return m_blocks[getIndex(x, y, z)].getId();
}

void Chunk::update()
{
    m_mesh = ChunkMeshBuilder::buildChunkMesh(*this);
    m_mesh.setPosition(Vector3f(m_position.x * 16, 0, m_position.y * 16));
}