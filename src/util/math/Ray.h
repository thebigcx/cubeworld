#pragma once

#include "Vector3.h"

#include <glm/glm.hpp>

class Ray
{
    public:
        Ray(glm::vec3 pos, glm::vec3 mag);

        glm::vec3 getMagnitude() const
        {
            return m_magnitude;
        }

        glm::vec3 getPosition() const
        {
            return m_position;
        }

    private:
        glm::vec3 m_position;
        glm::vec3 m_magnitude; // Normalised
};