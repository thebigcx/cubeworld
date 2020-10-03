#pragma once

#include <unordered_map>
#include <iostream>

#include <glm/glm.hpp>

#include <GL/glew.h>

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include "../texture/Glyph.h"

struct Character
{
    unsigned int textureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;
};

class TextRenderer
{
    public:
        TextRenderer();

        void renderText(const std::string& string, float x, float y, float scale, glm::vec3 color);

    private:
        FT_Library m_ft;
        FT_Face m_face;

        std::unordered_map<char, Glyph> m_characters;

        unsigned int m_vertArray, m_positions, m_texCoords, m_indices;

        static inline const int m_indexes[6] = {
            0, 1, 2,
            0, 2, 3
        };
};