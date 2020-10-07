#include "World.h"

#include "chunk/ChunkMeshBuilder.h"
#include "../player/Player.h"

World::World()
: m_chunkManager(*this, std::time(nullptr))
{
    
}

void World::render(ChunkRenderer& p_renderer)
{
    for (auto& chunk : m_chunkManager.getChunks())
    {
        p_renderer.render(chunk);
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
    int cx = (x / CHUNK_WIDTH);
    int cz = (z / CHUNK_WIDTH);

    int bx = abs(x % CHUNK_WIDTH);
    int bz = abs(z % CHUNK_WIDTH);

    std::cout << x << ", " << cx << ", " << bx << "\n";

    if (x < 0)
    {
        bx = 16 - bx;
    }
    if (z < 0)
    {
        bz = 16 - bz;
    }

    if (y < 0 || y >= CHUNK_HEIGHT)
    {
        return BlockType::Air;
    }

    if (!m_chunkManager.chunkExists(cx, cz))
    {
        return BlockType::Air;
    }
    
    return m_chunkManager.getChunk(cx, cz).getBlock(bx, y, bz);
}

void World::updateNeighbourChunks(int x, int z)
{
    m_chunkManager.updateNeighbourChunks(x, z);
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