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
#include "2D/Sprite.h"
#include "render/SpriteRenderer.h"
#include "render/TextRenderer.h"
#include "render/ChunkRenderer.h"

#include "resource/ResourceManager.h"

#include "util/Timer.h"
#include <../src/state/InGameState.h>

Game::Game()
{

}

void Game::run()
{
    Window window(1920, 1080, "CubeWorld");

    ResourceManager::init();

    Shader blockShader("shaders/block.vert", "shaders/basic.frag");
    Shader skyboxShader("shaders/skybox.vert", "shaders/skybox.frag");
    Shader orthoShader("shaders/ortho.vert", "shaders/basic.frag");
    Shader textShader("shaders/ortho.vert", "shaders/text.frag");

    ResourceManager::shaders.add("block", blockShader);
    ResourceManager::shaders.add("skybox", skyboxShader);
    ResourceManager::shaders.add("ortho", orthoShader);
    ResourceManager::shaders.add("text", textShader);
    
    InGameState inGameState(*this);

    TextRenderer textRenderer;
    ChunkRenderer chunkRenderer;

    Texture texture;
    texture.loadFile("res/terrain.png");
    ResourceManager::textures.add("terrainAtlas", texture);

    Texture crosshair;
    crosshair.loadFile("res/crosshair.png");
    ResourceManager::textures.add("crosshair", crosshair);
    Math::Random::initSeed();

    Font font;
    font.loadFile("res/Minecraftia.ttf");
    ResourceManager::fonts.add("minecraftia", font);

    Text fpsCounter(font);
    fpsCounter.setColor(glm::vec3(0.f, 0.f, 0.f));
    fpsCounter.setSize(Vector2f(48, 48));
    fpsCounter.setPosition(Vector2f(20, window.getSize().y - 100));

    Text positionText(font);
    positionText.setColor(glm::vec3(0.f, 0.f, 0.f));
    positionText.setSize(Vector2f(48, 48));
    positionText.setPosition(Vector2f(window.getSize().x - 300, window.getSize().y - 100));

    textRenderer.add(fpsCounter);
    textRenderer.add(positionText);

    Skybox skybox;

    Sprite sprite(ResourceManager::textures.get("crosshair"));
    sprite.setSize(Vector2f(20, 20));
    sprite.setPosition(Vector2f(window.getSize().x * 0.5f - 25, window.getSize().y * 0.5f - 25));

    SpriteRenderer spriteRenderer;
    spriteRenderer.add(sprite);

    glm::mat4 orthoProj = glm::ortho(0.f, (float)window.getSize().x, 0.f, (float)window.getSize().y, -1.f, 1.f);

    World world;

    Player player(window, world);

    ResourceManager::shaders.get("ortho").use();
    ResourceManager::shaders.get("ortho").setUniform("projection", orthoProj);

    ResourceManager::shaders.get("text").use();
    ResourceManager::shaders.get("text").setUniform("projection", orthoProj);
    ResourceManager::shaders.get("text").setUniform("model", glm::mat4(1.f));

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    double frames = 0;
    int fps = 0;
    time_t beginTime = std::time(nullptr);

    while (window.isOpen())
    {
        window.pollEvents();

        if (window.isKeyPressed(GLFW_KEY_ESCAPE))
        {
            window.close();
        }

        window.clear();

        skybox.render();

        player.handleInput(window);
        player.update(world);

        world.update(player);
        world.render(chunkRenderer);

        spriteRenderer.render();

        frames++;
        if (difftime(time(NULL), beginTime) >= 1.0)
        {
            fps = frames;
            frames = 0;
            beginTime = std::time(nullptr);
        }

        fpsCounter.setString(std::to_string(fps) + " FPS");

        glm::ivec3 playerPos = glm::ivec3(player.getPosition());
        std::string pos = std::to_string(playerPos.x) + ", " + std::to_string(playerPos.y) + ", " + std::to_string(playerPos.z);

        positionText.setString(pos);
        textRenderer.render();
        
        window.display();
    }
}
