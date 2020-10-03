#include "ResourceManager.h"

ResourceHolder<Texture> ResourceManager::textures;
ResourceHolder<Shader> ResourceManager::shaders;

void ResourceManager::init()
{
    static Texture tex;
    tex.loadFile("res/terrainAtlas.png");
    textures.setFailResource(tex);

    static Shader shader;
    shader.load("shaders/basic.vert", "shaders/basic.frag");
    shaders.setFailResource(shader);
}