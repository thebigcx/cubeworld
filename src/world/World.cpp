#include "World.h"

#include "chunk/ChunkMeshBuilder.h"

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
    int cx = x % CHUNK_WIDTH;
    int cz = z % CHUNK_WIDTH;
    if (x > 0 && x < m_chunkManager.getChunks().size() * CHUNK_WIDTH
     && y > 0 && y < CHUNK_HEIGHT
     && x > 0 && z < m_chunkManager.getChunks().size() * CHUNK_WIDTH)
    {
        return m_chunkManager.getChunk(floor(x/16), floor(z/16)).getBlock(cx, y, cz);
    }
    else
    {
        return BlockType::Air;
    }
}

void World::addChunkToUpdateList(int x, int z)
{
    m_chunkManager.addChunkToUpdateBatch(x, z);
}

void World::addChunkToUpdateList(Chunk& p_chunk)
{
    m_chunkManager.addChunkToUpdateBatch(p_chunk);
}

void World::update()
{
    m_chunkManager.update();
}