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
        Camera* m_camera;
        glm::mat4 m_projection;

        World* m_world;

        Vector3i getSelectedBlock(Ray ray, int rayOffset);

        double m_lastPlaceTime = 0;

        const double m_placeBlockDelay = 0.3; // In seconds
};