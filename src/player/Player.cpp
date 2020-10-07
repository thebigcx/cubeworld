#include "Player.h"

#include "../world/block/BlockManager.h"

#include <GLFW/glfw3.h>

Player::Player(Window& p_window, World& p_world)
: m_camera(p_window)
, m_mousePicker(m_camera, p_world)
{
    glm::vec3 spawnPoint(0, 0, 0);
    spawnPoint.y = 60;
    m_camera.setPosition(spawnPoint);
}

void Player::handleInput(Window& p_window)
{
    if (p_window.isKeyPressed(GLFW_KEY_SPACE))
    {
        m_camera.getVelocity() += m_camera.getSpeed() * glm::vec3(0, 1, 0);
    }
    if (p_window.isKeyPressed(GLFW_KEY_LEFT_SHIFT))
    {
        m_camera.getVelocity() -= m_camera.getSpeed() * glm::vec3(0, 1, 0);
    }

    m_camera.processInput(p_window);

    if (p_window.isMouseClicked(GLFW_MOUSE_BUTTON_LEFT))
    {
        m_mousePicker.checkBlockDestroy();
    }
    if (p_window.isMouseClicked(GLFW_MOUSE_BUTTON_RIGHT))
    {
        m_mousePicker.checkBlockPlace();
    }
}

void Player::update(World& p_world)
{
    m_onGround = false; // Reset for next update
    
    // Collisions

    m_camera.getPosition().x += m_camera.getVelocity().x;
    checkCollisions(p_world, glm::vec3(m_camera.getVelocity().x, 0, 0), m_camera.getPosition());
    
    m_camera.getPosition().y += m_camera.getVelocity().y;
    checkCollisions(p_world, glm::vec3(0, m_camera.getVelocity().y, 0), m_camera.getPosition());
    
    m_camera.getPosition().z += m_camera.getVelocity().z;
    checkCollisions(p_world, glm::vec3(0, 0, m_camera.getVelocity().z), m_camera.getPosition());
    
    m_camera.setVelocity(glm::vec3(0.f, 0.f, 0.f));
    
    m_camera.update();
}

void Player::checkCollisions(World& p_world, glm::vec3 p_velocity, glm::vec3& p_position)
{
    float pX = 1.f; // Player width
    float pY = 1.f; // Player height
    float pZ = 1.f; // Player depth

    auto cameraPos = m_camera.getPosition();

    for (int x = (int)cameraPos.x ; x < cameraPos.x + pX ; x++)
    for (int y = (int)cameraPos.y ; y < cameraPos.y + pY ; y++)
    for (int z = (int)cameraPos.z ; z < cameraPos.z + pZ ; z++)
    {
        auto block = p_world.getBlock(x, y, z);
        std::cout << BlockManager::getBlockData(block).collidable << "\n";
        if (BlockManager::getBlockData(block).collidable)
        {
            if (p_velocity.y > 0)
            {
                p_position.y = y - pY;
            }
            else if (p_velocity.y < 0)
            {
                p_position.y = y + pY;
                m_onGround = true;
            }

            if (p_velocity.x > 0)
            {
                p_position.x = x - pX;
            }
            else if (p_velocity.x < 0)
            {
                p_position.x = x + pX;
            }

            if (p_velocity.z > 0)
            {
                p_position.z = z - pZ;
            }
            else if (p_velocity.z < 0)
            {
                p_position.z = z + pZ;
            }
        }
    }
}
