#include "ChunkManager.h"

#include "../World.h"

#include "../../util/Timer.h"

ChunkManager::ChunkManager(World& p_world)
: m_world(&p_world)
{
    for (int x = 0 ; x < 20 ; x++)
    {
        for (int z = 0 ; z < 20 ; z++)
        {
            loadChunk(x, z);
        }
    }
    
}

Chunk& ChunkManager::loadChunk(int x, int z)
{
    if (!chunkExists(x, z))
    {
        m_chunks.push_back(Chunk(*m_world, Vector2i(x, z)));
        return m_chunks[m_chunks.size() - 1];
    }

    return m_world->getChunk(x, z);
}

bool ChunkManager::chunkExists(int x, int z)
{
    for (int i = 0 ; i < m_chunks.size() ; i++)
    {
        if (m_chunks[i].getPosition().x == x && m_chunks[i].getPosition().y == z)
        {
            return true;
        }
    }

    return false;
}

void ChunkManager::update()
{
    for (auto chunk : m_chunkUpdateBatch)
    {
        chunk->update();
    }
    m_chunkUpdateBatch.clear();
}

void ChunkManager::addChunkToUpdateBatch(int x, int z)
{
    m_chunkUpdateBatch.push_back(&m_chunks[getIndex(x, z)]);
}

void ChunkManager::addChunkToUpdateBatch(Chunk& p_chunk)
{
    m_chunkUpdateBatch.push_back(&p_chunk);
}

int ChunkManager::getIndex(int x, int z)
{
    for (int i = 0 ; i < m_chunks.size() ; i++)
    {
        if (m_chunks[i].getPosition().x == x && m_chunks[i].getPosition().y == z)
        {
            return i;
        }
    }

    return 0;
}

const Chunk& ChunkManager::getChunk(int x, int z)
{
    return m_chunks[getIndex(x, z)];
}