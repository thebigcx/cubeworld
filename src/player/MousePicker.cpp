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
        Vector3i rayPos = getSelectedBlock(ray, i/2);
        Vector3i blockPos(rayPos.x % CHUNK_WIDTH, rayPos.y, rayPos.z % CHUNK_WIDTH);
        Vector2i chunkPos(floor(rayPos.x / CHUNK_WIDTH), floor(rayPos.z / CHUNK_WIDTH));

        if (rayPos.x < 0 || rayPos.y < 0 || rayPos.y > CHUNK_HEIGHT || rayPos.z < 0)
        {
            continue;
        }
        
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

/*void MousePicker::checkBlockPlace()
{

}*/

Vector3i MousePicker::getSelectedBlock(Ray ray, int rayOffset)
{
    // Return the ray's start plus the direction it is heading, thus the block looking at
    int x = floor(ray.getPosition().x + (ray.getMagnitude().x * rayOffset));
    int y = floor(ray.getPosition().y + (ray.getMagnitude().y * rayOffset));
    int z = floor(ray.getPosition().z + (ray.getMagnitude().z * rayOffset));

    return Vector3i(x, y, z);
}