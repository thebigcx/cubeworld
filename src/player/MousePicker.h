#pragma once

#include "Camera.h"
#include "../world/World.h"
#include "../util/math/Ray.h"

class MousePicker
{
    public:
        MousePicker(Camera& p_cam, World& p_world);

        void checkBlockDestroy();
        void checkBlockPlace();

    private:
        Camera* m_pCamera;
        glm::mat4 m_projection;

        World* m_pWorld;

        Vector3i getSelectedBlock(const Ray& ray, int rayOffset);

        double m_lastPlaceTime = 0;
        double m_lastDestroyTime = 0;

        const double m_placeBlockDelay = 0.3; // In seconds
        const double m_destroyBlockDelay = 0.2; // In seconds
};