#include "Player.h"

#include <GLFW/glfw3.h>

Player::Player(Window& p_window, World& p_world)
: m_camera(p_window)
, m_mousePicker(m_camera, p_world)
{

}

void Player::handleInput(Window& p_window)
{
    m_camera.processInput(p_window);

    if (p_window.isMouseClicked(GLFW_MOUSE_BUTTON_LEFT))
    {
        m_mousePicker.blockPicked();
    }
}

void Player::update()
{
    m_camera.update();
}
