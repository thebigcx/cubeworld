#include "MousePicker.h"

MousePicker::MousePicker(Camera& p_camera, World& p_world)
: m_camera(&p_camera)
, m_projection(p_camera.getProjectionMatrix())
, m_world(&p_world)
{

}

void MousePicker::checkBlockDestroy()
{
    Ray ray(m_camera->getPosition(), m_camera->getDirection());

    for (int i = 0 ; i < 20 ; i++)
    {
        // Get the block coordinates
        Vector3i rayPos = getSelectedBlock(ray, i * 0.5f);
        Vector3i blockPos(rayPos.x % CHUNK_WIDTH, rayPos.y, rayPos.z % CHUNK_WIDTH);
        Vector2i chunkPos(floor(rayPos.x / CHUNK_WIDTH), floor(rayPos.z / CHUNK_WIDTH));
        
        // Get the chunk in which the block resides
        auto& chunk = m_world->getChunk(chunkPos.x, chunkPos.y);

        // Make sure that the block isn't already air
        if (chunk.getBlock(blockPos.x, blockPos.y, blockPos.z) != BlockType::Air)
        {
            // Set the block to air and update the chunk
            chunk.setBlock(blockPos, BlockType::Air);
            m_world->addChunkToUpdateList(chunk);
            break;
        }
    }
}

void MousePicker::checkBlockPlace()
{
    Ray ray(m_camera->getPosition(), m_camera->getDirection());

    Vector3i previous = getSelectedBlock(ray, 0);

    for (int i = 0 ; i < 20 ; i++)
    {
        // Get the position of the ray
        Vector3i rayPos = getSelectedBlock(ray, i * 0.5f);

        // Get the local chunk block coordinates
        Vector3i blockPos(rayPos.x % CHUNK_WIDTH, rayPos.y, rayPos.z % CHUNK_WIDTH);

        // Get the chunk coordinates
        Vector2i chunkPos(floor(rayPos.x / CHUNK_WIDTH), floor(rayPos.z / CHUNK_WIDTH));
        auto& chunk = m_world->getChunk(chunkPos.x, chunkPos.y);

        // If the selected block is solid, allow a block to be placed on it
        if (chunk.getBlock(blockPos.x, blockPos.y, blockPos.z) != BlockType::Air)
        {
            // Get the previous air block
            Vector3i previousBlockPos(previous.x % CHUNK_WIDTH, previous.y, previous.z % CHUNK_WIDTH);
            
            // Set it to dirt (for now) and update the chunk's mesh
            chunk.setBlock(previousBlockPos, BlockType::Dirt);
            m_world->addChunkToUpdateList(chunk);
            
            break;
        }

        previous = rayPos;
    }
}


Vector3i MousePicker::getSelectedBlock(Ray ray, int rayOffset)
{
    // Return the ray's start plus the direction it is heading, thus the block looking at
    int x = floor(ray.getPosition().x + (ray.getMagnitude().x * rayOffset));
    int y = floor(ray.getPosition().y + (ray.getMagnitude().y * rayOffset));
    int z = floor(ray.getPosition().z + (ray.getMagnitude().z * rayOffset));

    return Vector3i(x, y, z);
}