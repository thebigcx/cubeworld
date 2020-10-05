#include "ResourceManager.h"

ResourceHolder<Texture> ResourceManager::textures;
ResourceHolder<Shader> ResourceManager::shaders;
ResourceHolder<Font> ResourceManager::fonts;

void ResourceManager::init()
{
    static Texture tex;
    tex.loadFile("res/terrain.png");
    textures.setFailResource(tex);

    static Shader shader;
    shader.load("shaders/block.vert", "shaders/basic.frag");
    shaders.setFailResource(shader);

    static Font font;
    fonts.setFailResource(font);
}