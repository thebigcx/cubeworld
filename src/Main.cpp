#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Mesh.h"
#include "shader/Shader.h"
#include "Camera.h"
#include "world/Chunk.h"
#include "texture/TextureAtlas.h"

#include "resource/ResourceManager.h"

int main(int args, char** argsv)
{
    Window window(1920, 1080, "CubeWorld");

    ResourceManager::addShader("shader", Shader("shaders/shader.vert", "shaders/shader.frag"));
    ResourceManager::getShader("shader").use();

    float windowWidth = (float)window.getSize().x;
    float windowHeight = (float)window.getSize().y;
    float aspect = windowWidth / windowHeight;
    float fov = glm::radians(45.f);
    float nearPlane = 0.1f;
    float farPlane = 100.f;

    glm::mat4 projection = glm::perspective(fov, aspect, nearPlane, farPlane);

    ResourceManager::getShader("shader").setUniform("projection", projection);

    Texture texture;
    texture.loadFile("res/terrain.png");
    ResourceManager::addTexture("terrainAtlas", texture);

    Chunk chunk(Vector2i(0, 0));

    Camera camera;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

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

        chunk.render();

        window.display();
    }

    return 0;
}
