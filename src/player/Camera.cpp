#include "Camera.h"

#include "../resource/ResourceManager.h"

Camera::Camera()
{
    
}

void Camera::update()
{
    m_direction.x = cos(glm::radians(m_pan)) * cos(glm::radians(m_tilt));
    m_direction.y = sin(glm::radians(m_tilt));
    m_direction.z = sin(glm::radians(m_pan)) * cos(glm::radians(m_tilt));

    m_direction = glm::normalize(m_direction);

    m_viewMatrix = glm::lookAt(m_position, m_position + m_direction, m_up);

    ResourceManager::getShader("shader").use();
    ResourceManager::getShader("shader").setUniform("view", m_viewMatrix);
}

Camera& Camera::move(Vector3f p_dir)
{
    m_position.x += p_dir.x;
    m_position.y += p_dir.y;
    m_position.z += p_dir.z;
    return *this;
}

void Camera::processInput(Window& p_window)
{
    // Use some trigonometry to determine which way the camera should move
    // following different key presses
    if (p_window.isKeyPressed(GLFW_KEY_W))
    {
        m_position += m_speed * glm::vec3(cos(glm::radians(m_pan)), 0, sin(glm::radians(m_pan)));
    }
    if (p_window.isKeyPressed(GLFW_KEY_S))
    {
        m_position -= m_speed * glm::vec3(cos(glm::radians(m_pan)), 0, sin(glm::radians(m_pan)));
    }
    if (p_window.isKeyPressed(GLFW_KEY_A))
    {
        m_position -= m_speed * glm::normalize(glm::cross(m_direction, m_up));
    }
    if (p_window.isKeyPressed(GLFW_KEY_D))
    {
        m_position += m_speed * glm::normalize(glm::cross(m_direction, m_up));
    }
    if (p_window.isKeyPressed(GLFW_KEY_SPACE))
    {
        m_position += m_speed * glm::vec3(0, 1, 0);
    }
    if (p_window.isKeyPressed(GLFW_KEY_LEFT_SHIFT))
    {
        m_position -= m_speed * glm::vec3(0, 1, 0);
    }

    Vector2d mousePos = p_window.getMousePosition();

    float xoffset = mousePos.x - m_lastMousePos.x;
    float yoffset = mousePos.y - m_lastMousePos.y;

    m_pan += xoffset * m_sensitivity;
    m_tilt += -yoffset * m_sensitivity;
    m_tilt = Math::clamp(m_tilt, -89.5, 89.5);

    m_lastMousePos.x = mousePos.x;
    m_lastMousePos.y = mousePos.y;
}