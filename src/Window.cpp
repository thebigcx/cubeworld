#include "Window.h"

Window::Window(int p_width, int p_height, std::string p_title)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(p_width, p_height, p_title.c_str(), nullptr, nullptr);

    if (m_window == nullptr)
    {
        printf("Failed to create GLFW window.\n");
        glfwTerminate();
    }

    glfwSetWindowSizeLimits(m_window, 200, 200, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    glfwSetCursorPosCallback(m_window, mouse_callback);

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

    glfwSwapInterval(1);

    glViewport(0, 0, 1920, 1080);

    glfwMakeContextCurrent(m_window);

    glewInit();

    //glEnable(GL_MULTISAMPLE);
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

}

bool Window::isOpen()
{
    return !glfwWindowShouldClose(m_window);
}

void Window::clear(Color p_color)
{
    Color color = Color::normalise(p_color);
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::isKeyPressed(int p_key)
{
    return glfwGetKey(m_window, p_key);
}

Vector2d Window::getMousePosition()
{
    double xpos, ypos;
    glfwGetCursorPos(m_window, &xpos, &ypos);
    return Vector2d(xpos, ypos);
}

void Window::close()
{
    glfwSetWindowShouldClose(m_window, true);
}

void Window::display()
{
    glfwSwapBuffers(m_window);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

Vector2u Window::getSize() const
{
    int w, h;
    glfwGetWindowSize(m_window, &w, &h);
    if (w < 0 || h < 0)
    {
        return Vector2u(0, 0);
    }
    return Vector2u(w, h);
}