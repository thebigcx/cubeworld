#include "MousePicker.h"

MousePicker::MousePicker(Camera& p_camera, World& p_world)
: m_camera(&p_camera)
, m_projection(p_camera.getProjectionMatrix())
, m_world(&p_world)
{

}

void MousePicker::blockPicked()
{
    Ray ray(m_camera->getPosition(), m_camera->getDirection());

    Vector3f rayMag = ray.getMagnitude();
    Vector3f rayPos = ray.getPosition();

    for (int i = 0 ; i < 10 ; i++)
    {
        // Get the block coordinates
        int x = floor(rayPos.x + (rayMag.x * i));
        int y = floor(rayPos.y + (rayMag.y * i));
        int z = floor(rayPos.z + (rayMag.z * i));

        // Get the chunk in which the block resides
        auto& chunk = m_world->getChunk(floor(x / 16), floor(z / 16));

        // Make sure that the block isn't already air
        if (chunk.getBlock(x % 16, y & 16, z % 16).getId() != BlockType::Air)
        {
            // Set the block to air and update the chunk
            chunk.setBlock(Vector3i(x % 16, y % 16, z % 16), BlockType::Air);
            m_world->addChunkToUpdateList(floor(x / 16), floor(z / 16));
        }
    }
}