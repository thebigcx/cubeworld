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
#include "Sprite.h"
#include "render/SpriteRenderer.h"

#include "resource/ResourceManager.h"

Game::Game()
{

}

void Game::run()
{
    Window window(1920, 1080, "CubeWorld");

    ResourceManager::init();

    Shader basicShader("shaders/basic.vert", "shaders/basic.frag");
    Shader skyboxShader("shaders/skybox.vert", "shaders/skybox.frag");
    Shader orthoShader("shaders/ortho.vert", "shaders/basic.frag");

    ResourceManager::shaders.add("basic", basicShader);
    ResourceManager::shaders.add("skybox", skyboxShader);
    ResourceManager::shaders.add("ortho", orthoShader);

    Texture texture;
    texture.loadFile("res/terrain.png");
    ResourceManager::textures.add("terrainAtlas", texture);

    Texture crosshair;
    crosshair.loadFile("res/crosshair.png");
    ResourceManager::textures.add("crosshair", crosshair);
    Math::Random::initSeed();

    Skybox skybox;

    Sprite sprite(ResourceManager::textures.get("crosshair"));
    sprite.setSize(Vector2f(50, 50));
    sprite.setPosition(Vector2f(window.getSize().x * 0.5f - 25, window.getSize().y * 0.5f - 25));

    SpriteRenderer spriteRenderer;
    spriteRenderer.add(sprite);

    glm::mat4 orthoProj = glm::ortho(0.f, (float)window.getSize().x, 0.f, (float)window.getSize().y, -1.f, 1.f);

    World world;

    Player player(window, world);

    ResourceManager::shaders.get("ortho").use();
    ResourceManager::shaders.get("ortho").setUniform("projection", orthoProj);

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

        spriteRenderer.render();

        skybox.render();

        window.display();
    }
}