#pragma once

#include <unordered_map>
#include <iostream>
#include <vector>

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

        void add(Text& text);

        

        void render();
        
    private:
        unsigned int m_vertArray, m_positions, m_texCoords, m_indices;

        static inline const int m_indexes[6] = {
            0, 1, 2,
            0, 2, 3
        };

        std::vector<Text*> m_texts;

        void renderText(Text& text);
};