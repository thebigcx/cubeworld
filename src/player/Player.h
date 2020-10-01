#pragma once

#include "Camera.h"
#include "MousePicker.h"

class Player
{
    public:
        Player(Window& p_window, World& p_world);

        void handleInput(Window& p_window);
        void update();

    private:
        Camera m_camera;

        MousePicker m_mousePicker;
};