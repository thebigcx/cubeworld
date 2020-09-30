#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "util/math/Vector3.h"

#include "Window.h"

class Camera
{
    public:
        Camera();

        Camera& setPosition(Vector3f p_position)
        {
            m_position.x = p_position.x;
            m_position.y = p_position.y;
            m_position.z = p_position.z;
            return *this;
        }

        void update();

        void processInput(Window& p_window);

        Camera& move(Vector3f p_dir);

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
};