#include "ChunkManager.h"

#include "../World.h"
#include "../../player/Player.h"

#include "../../util/Timer.h"

ChunkManager::ChunkManager(World& p_world, long seed)
: m_world(&p_world)
{
    setSeed(seed);
}

Chunk& ChunkManager::loadChunk(int x, int z)
{
    if (!chunkExists(x, z))
    {
        m_chunks.push_back(Chunk(*m_world, Vector2i(x, z), m_seed));
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

void ChunkManager::update(Player& p_player)
{
    m_lastGenChunk.x++;
    if (m_lastGenChunk.x >= 16)
    {
        m_lastGenChunk.x = 0;
        m_lastGenChunk.y++;
    }
    if (m_lastGenChunk.y <= 16)
    {
        loadChunk(m_lastGenChunk.x, m_lastGenChunk.y);
        updateNeighbourChunks(m_lastGenChunk.x, m_lastGenChunk.y);
    }

    for (Chunk* chunk : m_chunkUpdateBatch)
    {
        chunk->update();
    }
    m_chunkUpdateBatch.clear();
}

void ChunkManager::updateNeighbourChunks(int x, int z)
{
    m_chunkUpdateBatch.push_back(&m_chunks[getIndex(x-1, z-1)]);
    m_chunkUpdateBatch.push_back(&m_chunks[getIndex(x-1, z+1)]);
    m_chunkUpdateBatch.push_back(&m_chunks[getIndex(x+1, z+1)]);
    m_chunkUpdateBatch.push_back(&m_chunks[getIndex(x+1, z-1)]);
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