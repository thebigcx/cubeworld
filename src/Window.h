#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "util/Color.h"
#include "util/math/Vector2.h"

class Window
{
    public:
        Window(int p_width, int p_height, std::string p_title);
        ~Window();

        void setActive();

        bool isOpen();

        void clear(Color p_color = Color::Black);

        void display();
        void pollEvents();

        bool isKeyPressed(int p_key);

        bool isMouseClicked(int p_button);

        Vector2d getMousePosition();

        void close();

        Vector2u getSize() const;

    private:
        GLFWwindow* m_window;

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

};