#pragma once

#include "Vector3.h"

class Ray
{
    public:
        Ray(Vector3f pos, Vector3f mag);

        bool intersectsWithPlane();

    private:
        Vector3f m_position;
        Vector3f m_magnitude; // Normalised
};