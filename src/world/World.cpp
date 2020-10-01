#include "World.h"

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

void World::addChunkToUpdateList(int x, int z)
{
    m_chunkManager.addChunkToUpdateBatch(x, z);
}

void World::update()
{
    m_chunkManager.update();
}