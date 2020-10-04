#pragma once

#include "ResourceHolder.h"
#include "../texture/Texture.h"
#include "../shader/Shader.h"
#include "../2D/text/Font.h"

struct ResourceManager
{
    public:
        static ResourceHolder<Texture> textures;
        static ResourceHolder<Shader>  shaders;
        static ResourceHolder<Font>    fonts;

        static void init();
};