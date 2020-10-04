#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../util/math/Vector2.h"
#include "../util/math/Rect.h"

class Transformable
{
    public:
        Transformable() {};

        int getRotation() const
        {
            return m_rotation;
        }

        Vector2f getSize() const
        {
            return m_size;
        }

        Vector2f getPosition() const
        {
            return m_position;
        }

        Transformable& setRotation(int p_rotation)
        {
            m_rotation = p_rotation;
            return *this;
        }

        Transformable& setSize(Vector2f p_size)
        {
            m_size = p_size;
            return *this;
        }
        
        Transformable& setPosition(Vector2f p_position)
        {
            m_position = p_position;
            return *this;
        }
        
        Transformable& setOrigin(Vector2f p_origin)
        {
            m_origin = p_origin;
            return *this;
        }

        Transformable& move(Vector2f p_direction)
        {
            m_position.x += p_direction.x;
            m_position.y += p_direction.y;
            return *this;
        }

        Transformable& rotate(int p_rot)
        {
            m_rotation += p_rot;
            m_rotation = m_rotation % 360;
            return *this;
        }

        FloatRect getBounds() const
        {
            FloatRect r;
            r.x = m_position.x;
            r.y = m_position.y;
            r.width = m_size.x;
            r.height = m_size.y;
            return r;
        }

        glm::mat4 getTransformationMatrix() const
        {
            glm::mat4 matrix(1.f);

            glm::vec3 pos(m_position.x, m_position.y, 0.f);
            glm::vec3 scalar(m_size.x, m_size.y, 1.f);

            matrix = glm::translate(matrix, pos);

            matrix = glm::translate(matrix, glm::vec3(m_origin.x * m_size.x, m_origin.y * m_size.y, 0.f));
            matrix = glm::rotate(matrix, glm::radians((float)m_rotation), glm::vec3(0.f, 0.f, 1.f));
            matrix = glm::translate(matrix, glm::vec3(-m_origin.x * m_size.x, -m_origin.y * m_size.y, 0.f));

            matrix = glm::scale(matrix, scalar);

            return matrix;
        }

    protected:
        int m_rotation = 0;

        Vector2f m_size;
        Vector2f m_position;

        Vector2f m_origin;
};