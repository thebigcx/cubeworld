#pragma once

#include <unordered_map>
#include <string>

#include "../shader/Shader.h"
#include "../texture/Texture.h"

class ResourceManager
{
    public:
        static std::unordered_map<std::string, Shader> shaders;
        static std::unordered_map<std::string, Texture> textures;

        static void addShader(const std::string& p_name, Shader p_shader);
        static void addTexture(const std::string& p_name, Texture p_texture);

        static Shader& getShader(const std::string& p_name);
        static Texture& getTexture(const std::string& p_name);

        static bool doesShaderExist(const std::string& p_name);
        static bool doesTextureExist(const std::string& p_name);
};