#pragma once

#include "Camera.h"
#include "MousePicker.h"

class Player
{
    public:
        Player(Window& p_window, World& p_world);

        void handleInput(Window& p_window);
        void update(World& p_world);
        void checkCollisions(World& p_world, glm::vec3 p_velocity, glm::vec3& p_position);

        const glm::vec3& getPosition()
        {
            return m_camera.getPosition();
        }

        Camera& getCamera()
        {
            return m_camera;
        }

    private:
        Camera m_camera;

        MousePicker m_mousePicker;

        glm::vec3 m_velocity;

        bool m_onGround = false;
};