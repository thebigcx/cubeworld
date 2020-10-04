#pragma once

#include <unordered_map>
#include <iostream>

#include <glm/glm.hpp>

#include <GL/glew.h>

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include "../2D/text/Glyph.h"
#include "../2D/text/Font.h"
#include "../2D/text/Text.h"

class TextRenderer
{
    public:
        TextRenderer();

        void renderText(Text& text);
        
        void renderText(Font& font, const std::string& string, float x, float y, float scale, glm::vec3 color);

    private:
        Font m_font;

        unsigned int m_vertArray, m_positions, m_texCoords, m_indices;

        static inline const int m_indexes[6] = {
            0, 1, 2,
            0, 2, 3
        };
};