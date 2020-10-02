#include "Game.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Mesh.h"
#include "shader/Shader.h"
#include "player/Player.h"
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

    Texture texture;
    texture.loadFile("res/terrain.png");
    ResourceManager::addTexture("terrainAtlas", texture);

    Math::Random::initSeed();

    Skybox skybox;

    World world;
    world.getChunk(0, 0).setBlock(Vector3i(0, 0, 0), BlockType::Grass);
    for (int i = 0 ; i < 10 ; i++)
    {
        world.getChunk(0, 0).setBlock(Vector3i(i, 0, 0), BlockType::Grass);
    }
    world.addChunkToUpdateList(0, 0);

    Player player(window, world);

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

        player.handleInput(window);
        player.update(world);

        world.update(player);
        world.render();

        skybox.render();

        window.display();
    }
}