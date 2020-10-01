#pragma once

#include "Vector3.h"

class Ray
{
    public:
        Ray(Vector3f pos, Vector3f mag);

        bool intersectsWithPlane();

        Vector3f getMagnitude()
        {
            return m_magnitude;
        }

        Vector3f getPosition()
        {
            return m_position;
        }

    private:
        Vector3f m_position;
        Vector3f m_magnitude; // Normalised
};