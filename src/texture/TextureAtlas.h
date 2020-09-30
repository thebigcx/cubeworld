#pragma once

#include <array>

#include "../util/math/Vector2.h"

struct TextureAtlas
{
    public:
        static std::array<Vector2f, 4> getTexture(Vector2i p_pos)
        {
            float x  = (float)p_pos.x / (atlasSize / textureSize);
            float sx = ((float)p_pos.x + 1) / (atlasSize / textureSize);

            float y  = 1 - ((float)p_pos.y / (atlasSize / textureSize));
            float sy = 1 - (((float)p_pos.y + 1) / (atlasSize / textureSize));

            std::array<Vector2f, 4> texCoords = {
                Vector2f(x,  y),
                Vector2f(sx, y),
                Vector2f(sx, sy),
                Vector2f(x,  sy),
            };

            return texCoords;
        }

    private:
        static const int atlasSize = 256;
        static const int textureSize = 16;
};