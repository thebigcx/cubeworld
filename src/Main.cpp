#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "TextureAtlas.h"

#include "resource/ResourceManager.h"

int main(int args, char** argsv)
{
    Window window(1920, 1080, "CubeWorld");

    ResourceManager::addShader("shader", Shader("shaders/shader.vert", "shaders/shader.frag"));
    ResourceManager::getShader("shader").use();

    glm::mat4 projection = glm::perspective(glm::radians(45.f), 1920.f/1080.f, 0.1f, 100.f);

    ResourceManager::getShader("shader").setUniform("projection", projection);

    Mesh mesh;
    std::array<Vector3f, 4> positions = {
        Vector3f( 0.5f,  0.5f, 0.5f),
        Vector3f( 0.5f, -0.5f, 0.5f),
        Vector3f(-0.5f, -0.5f, 0.5f),
        Vector3f(-0.5f,  0.5f, 0.5f)
    };

    mesh.addFace(positions, TextureAtlas::getTexture(Vector2f(8, 15)));
    mesh.update();

    Camera camera;

    glEnable(GL_DEPTH_TEST);

    while (window.isOpen())
    {
        window.pollEvents();

        if (window.isKeyPressed(GLFW_KEY_ESCAPE))
        {
            window.close();
        }

        window.clear();

        

        camera.processInput(window);

        camera.update();

        mesh.render();

        window.display();
    }

    return 0;
}
