#include "ResourceManager.h"

ResourceHolder<Texture> ResourceManager::textures;
ResourceHolder<Shader> ResourceManager::shaders;
ResourceHolder<Font> ResourceManager::fonts;

void ResourceManager::init()
{
    static Texture tex;
    tex.loadFile("res/terrainAtlas.png");
    textures.setFailResource(tex);

    static Shader shader;
    shader.load("shaders/basic.vert", "shaders/basic.frag");
    shaders.setFailResource(shader);

    static Font font;
    fonts.setFailResource(font);
}