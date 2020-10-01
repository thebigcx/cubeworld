#include "Game.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Mesh.h"
#include "shader/Shader.h"
#include "player/Camera.h"
#include "world/chunk/Chunk.h"
#include "texture/TextureAtlas.h"
#include "world/World.h"
#include "texture/Skybox.h"

#include "resource/ResourceManager.h"

Game::Game()
{

}

void Game::run()
{
    Window window(1920, 1080, "CubeWorld");

    ResourceManager::addShader("shader", Shader("shaders/basic.vert", "shaders/basic.frag"));
    ResourceManager::addShader("skybox", Shader("shaders/skybox.vert", "shaders/skybox.frag"));

    ResourceManager::getShader("shader").use();

    float windowWidth = (float)window.getSize().x;
    float windowHeight = (float)window.getSize().y;
    float aspect = windowWidth / windowHeight;
    float fov = glm::radians(45.f);
    float nearPlane = 0.1f;
    float renderDistance = 3000.f;

    glm::mat4 projection = glm::perspective(fov, aspect, nearPlane, renderDistance);

    ResourceManager::getShader("shader").setUniform("projection", projection);

    ResourceManager::getShader("skybox").use();
    ResourceManager::getShader("skybox").setUniform("projection", projection);

    Texture texture;
    texture.loadFile("res/terrain.png");
    ResourceManager::addTexture("terrainAtlas", texture);

    Math::Random::initSeed();

    std::vector<std::string> faces = {
        "res/skybox.png",
        "res/skybox.png",
        "res/skybox.png",
        "res/skybox.png",
        "res/skybox.png",
        "res/skybox.png"
    };
    Skybox skybox(faces);

    World world;
    world.getChunk(0, 0).setBlock(Vector3i(0, 0, 0), BlockType::Grass);
    for (int i = 0 ; i < 10 ; i++)
    {
        world.getChunk(0, 0).setBlock(Vector3i(i, 0, 0), BlockType::Grass);
    }
    world.addChunkToUpdateList(0, 0);

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

        world.update();
        world.render();

        ResourceManager::getShader("skybox").use();
        auto view = glm::mat4(glm::mat3(camera.getViewMatrix()));
        ResourceManager::getShader("skybox").setUniform("view", view);

        skybox.render();

        window.display();
    }
}