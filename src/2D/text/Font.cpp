#include "Font.h"

Font::Font()
{

}

bool Font::loadFile(const std::string& path)
{
    // Initialise FreeType
    if (FT_Init_FreeType(&m_ft))
    {
        std::cout << "Unable to initialise FreeType.\n";
        return false;
    }

    if (FT_New_Face(m_ft, path.c_str(), 0, &m_face))
    {
        std::cout << "Unable to load font.\n";
        return false;
    }

    FT_Set_Pixel_Sizes(m_face, 0, 48);

    // Load the character glyphs
    for (unsigned char c = 0 ; c < 255 ; c++) // 1 Byte per character
    {
        m_characters.insert(std::make_pair(c, loadGlyph(c)));
    }

    // Free memory
    FT_Done_Face(m_face);
    FT_Done_FreeType(m_ft);

    return true;
}

Glyph Font::loadGlyph(char character) const
{
    if (FT_Load_Char(m_face, character, FT_LOAD_RENDER))
    {
        std::cout << "Unable to load glyph.\n";
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        m_face->glyph->bitmap.width,
        m_face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        m_face->glyph->bitmap.buffer
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Glyph glyph(
        texture,
        glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows),
        glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
        m_face->glyph->advance.x
    );

    return glyph;
}