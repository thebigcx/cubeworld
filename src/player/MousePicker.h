#pragma once

#include "Camera.h"
#include "../world/World.h"
#include "../util/math/Ray.h"

class MousePicker
{
    public:
        MousePicker(Camera& p_cam, World& p_world);

        void blockPicked();

    private:
        Camera* m_camera;
        glm::mat4 m_projection;

        World* m_world;
};