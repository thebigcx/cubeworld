#include "ResourceManager.h"

std::unordered_map<std::string, Shader> ResourceManager::shaders;
//std::unordered_map<std::string, Texture> ResourceManager::textures;

void ResourceManager::addShader(std::string p_name, Shader p_shader)
{
    shaders.insert(std::make_pair(p_name, p_shader));
}

/*void ResourceManager::addTexture(std::string p_name, Texture p_texture)
{
    textures.insert(std::make_pair(p_name, p_texture));
}*/


Shader& ResourceManager::getShader(std::string p_name)
{
    if (doesShaderExist(p_name))
    {
        return shaders.at(p_name);
    }
    else
    {
        throw std::runtime_error("Shader does not exist.\n");
    }   
}

/*Texture& ResourceManager::getTexture(std::string p_name)
{
    if (doesTextureExist(p_name))
    {
        return textures.at(p_name);
    }
    else
    {
        throw std::runtime_error("Texture does not exist.\n");
    }   
}*/

bool ResourceManager::doesShaderExist(std::string p_name)
{
    return shaders.find(p_name) != shaders.end();
}

/*bool ResourceManager::doesTextureExist(std::string p_name)
{
    return textures.find(p_name) != textures.end();
}*/