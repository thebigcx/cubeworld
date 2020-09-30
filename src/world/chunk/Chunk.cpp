#include "Chunk.h"

#include "../../texture/TextureAtlas.h"
#include "../block/BlockVertices.h"
#include "../block/BlockManager.h"
#include "../../util/math/Vector3.h"

Chunk::Chunk(Vector2i p_position)
: m_position(p_position)
{
    for (int x = 0 ; x < CHUNK_WIDTH ; x++)
    {
        for (int y = 0 ; y < CHUNK_HEIGHT ; y++)
        {
            for (int z = 0 ; z < CHUNK_WIDTH ; z++)
            {

                
                auto block = BlockManager::getBlock(m_blocks[getIndex(x, y, z)]);
                m_mesh.addFace(BlockVertices::front, TextureAtlas::getTexture(block.texCoordBottom), Vector3i(x, y, z));
            }
        }
    }
    
    m_mesh.update();
}

void Chunk::render()
{
    m_mesh.render();
}

int Chunk::getIndex(int x, int y, int z)
{
    return x * CHUNK_WIDTH + y * CHUNK_HEIGHT + z;
}