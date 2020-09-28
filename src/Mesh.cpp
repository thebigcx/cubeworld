#include "Mesh.h"

Mesh::Mesh()
{
    ResourceManager::getShader("shader").use();

    model = glm::mat4(1.f);

    glGenVertexArrays(1, &m_array);
    glBindVertexArray(m_array);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glGenBuffers(1, &m_elementBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Mesh::render()
{
    ResourceManager::getShader("shader").use();
    ResourceManager::getShader("shader").setUniform("model", model);
    glBindVertexArray(m_array);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}