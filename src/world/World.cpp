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