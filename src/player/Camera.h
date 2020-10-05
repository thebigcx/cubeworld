#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../util/math/Vector3.h"

#include "../Window.h"

class Camera
{
    public:
        Camera(Window& p_window);

        void setPosition(glm::vec3 p_position)
        {
            m_position = p_position;
        }

        void setVelocity(glm::vec3 p_velocity)
        {
            m_velocity = p_velocity;
        }

        void update();

        void processInput(Window& p_window);

        Camera& move(glm::vec3 p_dir);

        glm::mat4 getViewMatrix()
        {
            return m_viewMatrix;
        }

        glm::mat4 getProjectionMatrix()
        {
            return m_projectionMatrix;
        }

        glm::vec3& getPosition()
        {
            return m_position;
        }

        glm::vec3& getDirection()
        {
            return m_direction;
        }

        glm::vec3& getVelocity()
        {
            return m_velocity;
        }

        float getSpeed()
        {
            return m_speed;
        }

    private:
        glm::mat4 m_viewMatrix;
        glm::mat4 m_projectionMatrix;

        glm::vec3 m_position = glm::vec3(0.f, 0.f, 0.f);
        glm::vec3 m_direction = glm::vec3(0.f, 0.f, -1.f);
        glm::vec3 m_up = glm::vec3(0.f, 1.f, 0.f);

        Vector2f m_lastMousePos = Vector2f(1000, 500);

        float m_pan, m_tilt;

        float m_sensitivity = 0.1f;
        const float m_speed = 0.5f;

        glm::vec3 m_velocity;
};