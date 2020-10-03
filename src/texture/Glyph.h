#pragma once

#include <glm/glm.hpp>

class Glyph
{
    public:
        Glyph() {}
        
        Glyph(unsigned int texture, glm::ivec2 size, glm::ivec2 bearing, unsigned int advance);

        unsigned int getTexture()
        {
            return m_texture;
        }

        glm::ivec2 getSize()
        {
            return m_size;
        }

        glm::ivec2 getBearing()
        {
            return m_bearing;
        }

        unsigned int getAdvance()
        {
            return m_advance;
        }

    private:
        unsigned int m_texture;
        glm::ivec2 m_size;
        glm::ivec2 m_bearing;
        unsigned int m_advance;
};