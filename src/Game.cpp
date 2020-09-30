#include "Game.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Mesh.h"
#include "shader/Shader.h"
#include "Camera.h"
#include "world/chunk/Chunk.h"
#include "texture/TextureAtlas.h"
#include "world/World.h"

#include "resource/ResourceManager.h"

Game::Game()
{

}

void Game::run()
{
    Window window(1920, 1080, "CubeWorld");

    ResourceManager::addShader("shader", Shader("shaders/shader.vert", "shaders/shader.frag"));
    ResourceManager::getShader("shader").use();

    float windowWidth = (float)window.getSize().x;
    float windowHeight = (float)window.getSize().y;
    float aspect = windowWidth / windowHeight;
    float fov = glm::radians(45.f);
    float nearPlane = 0.1f;
    float renderDistance = 300.f;

    glm::mat4 projection = glm::perspective(fov, aspect, nearPlane, renderDistance);

    ResourceManager::getShader("shader").setUniform("projection", projection);

    Texture texture;
    texture.loadFile("res/terrain.png");
    ResourceManager::addTexture("terrainAtlas", texture);

    Math::Random::initSeed();

    World world;

    Camera camera;

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
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

        world.render();

        window.display();
    }
}