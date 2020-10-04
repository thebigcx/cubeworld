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

#include "resource/ResourceManager.h"

#include "util/Timer.h"

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
    Shader textShader("shaders/ortho.vert", "shaders/text.frag");

    ResourceManager::shaders.add("basic", basicShader);
    ResourceManager::shaders.add("skybox", skyboxShader);
    ResourceManager::shaders.add("ortho", orthoShader);
    ResourceManager::shaders.add("text", textShader);

    TextRenderer textRenderer;

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

    Text text(font);
    text.setString("Hello");
    text.setColor(glm::vec3(0.f, 0.f, 0.f));
    text.setPosition(Vector2f(100, 100));

    Skybox skybox;

    Sprite sprite(ResourceManager::textures.get("crosshair"));
    sprite.setSize(Vector2f(20, window.getSize().y - 100));
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

        player.handleInput(window);
        player.update(world);

        world.update(player);
        world.render();

        skybox.render();

        spriteRenderer.render();

        frames++;
        if (difftime(time(NULL), beginTime) >= 1.0)
        {
            fps = frames;
            frames = 0;
            beginTime = std::time(nullptr);
        }
        text.setString(std::to_string(fps) + " FPS");
        textRenderer.renderText(text);

        /*textRenderer.renderText(ResourceManager::fonts.get("minecraftia"), 
                                std::to_string(fps) + " FPS", 
                                20, 
                                window.getSize().y - 100, 
                                1, 
                                glm::vec3(0.f, 0.f, 0.f));*/
        
        window.display();
    }
}