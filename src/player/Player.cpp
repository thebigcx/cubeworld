#include "Player.h"

#include "../world/block/BlockManager.h"

#include <GLFW/glfw3.h>

Player::Player(Window& p_window, World& p_world)
: m_camera(p_window)
, m_mousePicker(m_camera, p_world)
{

}

void Player::handleInput(Window& p_window)
{
    m_camera.processInput(p_window);

    if (p_window.isMouseClicked(GLFW_MOUSE_BUTTON_LEFT))
    {
        m_mousePicker.checkBlockDestroy();
    }
}

void Player::update(World& p_world)
{
    m_camera.getPosition().x += m_camera.getVelocity().x;
    checkCollisions(p_world, glm::vec3(m_camera.getVelocity().x, 0, 0), m_camera.getPosition());
    
    m_camera.getPosition().y += m_camera.getVelocity().y;
    checkCollisions(p_world, glm::vec3(0, m_camera.getVelocity().y, 0), m_camera.getPosition());
    
    m_camera.getPosition().z += m_camera.getVelocity().z;
    checkCollisions(p_world, glm::vec3(0, 0, m_camera.getVelocity().z), m_camera.getPosition());
    
    m_camera.getVelocity() = glm::vec3(0.f);
    
    m_camera.update();
}

void Player::checkCollisions(World& p_world, glm::vec3 p_velocity, glm::vec3& p_position)
{
    for (int x = m_camera.getPosition().x - 1 ; x < m_camera.getPosition().x + 1 ; x++)
    for (int y = m_camera.getPosition().y - 1 ; y < m_camera.getPosition().y + 1 ; y++)
    for (int z = m_camera.getPosition().z - 1 ; z < m_camera.getPosition().z + 1 ; z++)
    {
        auto block = p_world.getBlock(x, y, z);
        if (BlockManager::getBlockData(block).collidable)
        {
            if (p_velocity.y > 0)
            {
                p_position.y = y - 1;
            }
            else if (p_velocity.y < 0)
            {
                p_position.y = y + 2;
            }

            if (p_velocity.x > 0)
            {
                p_position.x = x - 1;
            }
            else if (p_velocity.x < 0)
            {
                p_position.x = x + 2;
            }

            if (p_velocity.z > 0)
            {
                p_position.z = z - 1;
            }
            else if (p_velocity.z < 0)
            {
                p_position.z = z + 2;
            }
        }
    }
}