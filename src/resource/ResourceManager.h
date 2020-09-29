#pragma once

#include <unordered_map>
#include <string>

#include "../Shader.h"
#include "../Texture.h"

class ResourceManager
{
    public:
        static std::unordered_map<std::string, Shader> shaders;
        static std::unordered_map<std::string, Texture> textures;

        static void addShader(std::string p_name, Shader p_shader);
        static void addTexture(std::string p_name, Texture p_texture);

        static Shader& getShader(std::string p_name);
        static Texture& getTexture(std::string p_name);

        static bool doesShaderExist(std::string p_name);
        static bool doesTextureExist(std::string p_name);
};