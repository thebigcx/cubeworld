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
    int x = (p_player.getCamera().getPosition().x / CHUNK_WIDTH) - 3;
    int z = (p_player.getCamera().getPosition().z / CHUNK_WIDTH) - 3;
    
    for (int i = x ; i < x + 6 ; i++)
    for (int j = z ; j < z + 6 ; j++)
    {
        if (!chunkExists(i, j))
        {
            loadChunk(i, j);
            updateNeighbourChunks(i, j);
            break;
        }
    }
    
    for (Chunk* chunk : m_chunkUpdateBatch)
    {
        chunk->update();
    }
    m_chunkUpdateBatch.clear();
}

void ChunkManager::updateNeighbourChunks(int x, int z)
{
    if (getIndex(x - 1, z - 1) != -1);
        //m_chunkUpdateBatch.push_back(&m_chunks[getIndex(x - 1, z - 1)]);

    if (getIndex(x - 1, z + 1) != -1);
        //m_chunkUpdateBatch.push_back(&m_chunks[getIndex(x - 1, z + 1)]);

    if (getIndex(x + 1, z + 1) != -1);
        //m_chunkUpdateBatch.push_back(&m_chunks[getIndex(x + 1, z + 1)]);

    if (getIndex(x + 1, z - 1) != -1);
        //m_chunkUpdateBatch.push_back(&m_chunks[getIndex(x + 1, z - 1)]);
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

    return -1;
}

const Chunk& ChunkManager::getChunk(int x, int z)
{
    return m_chunks[getIndex(x, z)];
}
