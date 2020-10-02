#pragma once

#include "Vector3.h"

#include <glm/glm.hpp>

class Ray
{
    public:
        Ray(glm::vec3 pos, glm::vec3 mag);

        bool intersectsWithPlane();

        glm::vec3 getMagnitude()
        {
            return m_magnitude;
        }

        glm::vec3 getPosition()
        {
            return m_position;
        }

    private:
        glm::vec3 m_position;
        glm::vec3 m_magnitude; // Normalised
};