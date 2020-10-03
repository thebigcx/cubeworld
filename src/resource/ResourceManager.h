#pragma once

#include "ResourceHolder.h"
#include "../texture/Texture.h"
#include "../shader/Shader.h"

struct ResourceManager
{
    public:
        static ResourceHolder<Texture> textures;
        static ResourceHolder<Shader> shaders;

        static void init();
};