#include "ChunkManager.h"

#include "../World.h"

ChunkManager::ChunkManager(World& p_world)
: m_world(&p_world)
{
    m_chunks.push_back(Chunk(Vector2i(0, 0)));
}