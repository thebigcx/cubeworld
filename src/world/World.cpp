#include "World.h"

#include "chunk/ChunkMeshBuilder.h"
#include "../player/Player.h"

World::World()
: m_chunkManager(*this)
{
    
}

void World::render()
{
    for (auto& chunk : m_chunkManager.getChunks())
    {
        chunk.render();
    }
}

Chunk& World::getChunk(int x, int z)
{
    for (auto& chunk : m_chunkManager.getChunks())
    {
        if (chunk.getPosition().x == x && chunk.getPosition().y == z)
        {
            return chunk;
        }
    }

    return m_chunkManager.loadChunk(x, z);
}

int World::getBlock(int x, int y, int z)
{
    int cx = x / CHUNK_WIDTH;
    int cz = z / CHUNK_WIDTH;

    int bx = x % CHUNK_WIDTH;
    int bz = z % CHUNK_WIDTH;

    if (x < 0 || y < 0 || z < 0 || y > CHUNK_HEIGHT)
    {
        return BlockType::Air;
    }
    
    return m_chunkManager.getChunk(cx, cz).getBlock(bx, y, bz);
}

void World::addChunkToUpdateList(int x, int z)
{
    m_chunkManager.addChunkToUpdateBatch(x, z);
}

void World::addChunkToUpdateList(Chunk& p_chunk)
{
    m_chunkManager.addChunkToUpdateBatch(p_chunk);
}

void World::update(Player& p_player)
{
    m_chunkManager.update(p_player);
}