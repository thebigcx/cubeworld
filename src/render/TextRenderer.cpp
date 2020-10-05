#include "TextRenderer.h"

#include "../resource/ResourceManager.h"

#include "../util/Timer.h"

TextRenderer::TextRenderer()
{
    m_font.loadFile("res/Minecraftia.ttf");


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
}

void TextRenderer::add(Text& text)
{
    m_texts.push_back(&text);
}

void TextRenderer::render()
{
    for (auto& text : m_texts)
    {
        this->renderText(*text);
    }
}

void TextRenderer::renderText(Text& text)
{
    ResourceManager::shaders.get("text").use();

    ResourceManager::shaders.get("text").setUniform("textColor", text.getColor());

    glBindVertexArray(m_vertArray);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    float x = text.getPosition().x;
    float y = text.getPosition().y;

    glm::vec2 scale(text.getSize().x / text.getFont()->getSize(), text.getSize().y / text.getFont()->getSize());

    std::string::const_iterator c;
    for (c = text.getString().begin() ; c != text.getString().end() ; c++)
    {
        Glyph& character = text.getFont()->getCharacters()[*c];

        float xPos = x + character.getBearing().x * scale.x;
        float yPos = y - (character.getSize().y - character.getBearing().y) * scale.y;

        float w = character.getSize().x * scale.x; // scale
        float h = character.getSize().y * scale.y; // scale

        glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(xPos, yPos, 0.f));
        model = glm::scale(model, glm::vec3(w, h, 1.f));

        ResourceManager::shaders.get("text").setUniform("model", model);

        glBindTexture(GL_TEXTURE_2D, character.getTexture());

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        x += (character.getAdvance() >> 6) * scale.x; // scale
    }

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}