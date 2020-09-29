#pragma once

#include <array>

#include "util/Vector2.h"

struct TextureAtlas
{
    public:
        static std::array<Vector2f, 4> getTexture(Vector2f p_pos)
        {
            float pixelSize = 1.f / atlasSize;

            float x  = ((p_pos.x * textureSize) - 0.5f * pixelSize);
            float y  = ((p_pos.y * textureSize) - 0.5f * pixelSize);
            float sx = ((x + textureSize) - pixelSize);
            float sy = ((y + textureSize) - pixelSize);

            std::array<Vector2f, 4> texCoords = {
                Vector2f(sx, sy),
                Vector2f(sx, y),
                Vector2f(x,  y),
                Vector2f(x,  sy)
            };

            return texCoords;
        }

    private:
        static const int atlasSize = 256;
        static const int textureSize = 16;
};