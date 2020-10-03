#include "TextRenderer.h"

#include "../resource/ResourceManager.h"

#include "../util/Timer.h"

TextRenderer::TextRenderer()
{
    if (FT_Init_FreeType(&m_ft))
    {
        std::cout << "Unable to initialise FreeType.\n";
    }

    if (FT_New_Face(m_ft, "res/Minecraftia.ttf", 0, &m_face))
    {
        std::cout << "Unable to load font.\n";
    }

    FT_Set_Pixel_Sizes(m_face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    

    for (unsigned char c = 0 ; c < 128 ; c++)
    {
        if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
        {
            std::cout << "Unable to load glyph.\n";
            continue;
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

        Glyph character(
            texture,
            glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows),
            glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
            m_face->glyph->advance.x
        );
        m_characters.insert(std::make_pair(c, character));
    }

    FT_Done_Face(m_face);
    FT_Done_FreeType(m_ft);


    glGenVertexArrays(1, &m_vertArray);
    glGenBuffers(1, &m_positions);
    glGenBuffers(1, &m_texCoords);
    glGenBuffers(1, &m_indices);

    glBindVertexArray(m_vertArray);

    float positions[] = {
        1.f, 1.f,
        0.f, 1.f,
        0.f, 0.f,
        1.f, 0.f
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_positions);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    float texCoords[] = {
        1.f, 0.f,
        0.f, 0.f,
        0.f, 1.f,
        1.f, 1.f
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_texCoords);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), m_indexes, GL_STATIC_DRAW);
    //glBufferData();
}

void TextRenderer::renderText(const std::string& string, float x, float y, float scale, glm::vec3 color)
{
    ResourceManager::shaders.get("text").use();

    ResourceManager::shaders.get("text").setUniform("textColor", color);

    glBindVertexArray(m_vertArray);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    std::string::const_iterator c;
    for (c = string.begin() ; c != string.end() ; c++)
    {
        Glyph& character = m_characters[*c];

        float xPos = x + character.getBearing().x * scale;
        float yPos = y - (character.getSize().y - character.getBearing().y) * scale;

        float w = character.getSize().x * scale;
        float h = character.getSize().y * scale;

        glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(xPos, yPos, 0.f));
        model = glm::scale(model, glm::vec3(w, h, 1.f));

        ResourceManager::shaders.get("text").setUniform("model", model);

        glBindTexture(GL_TEXTURE_2D, character.getTexture());

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        x += (character.getAdvance() >> 6) * scale;
    }

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}