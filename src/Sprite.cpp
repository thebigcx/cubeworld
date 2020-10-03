#include "Sprite.h"

#include <glm/gtc/matrix_transform.hpp>

Sprite::Sprite(const Texture& p_texture)
: m_pTexture(&p_texture)
{
    glGenVertexArrays(1, &m_vertArray);
    glBindVertexArray(m_vertArray);

    glGenBuffers(1, &m_positionBuf);
    glBindBuffer(GL_ARRAY_BUFFER, m_positionBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, m_positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glGenBuffers(1, &m_texCoordBuf);
    glBindBuffer(GL_ARRAY_BUFFER, m_texCoordBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, m_texCoords, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);


    glGenBuffers(1, &m_elementBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 6, m_indices, GL_STATIC_DRAW);

    setSize(Vector2f(m_pTexture->getSize().x, m_pTexture->getSize().y));
    //m_model = glm::scale(glm::mat4(1.f), glm::vec3(100.f, 100.f, 1.f));
}