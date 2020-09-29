#include "Mesh.h"

Mesh::Mesh()
{
    ResourceManager::getShader("shader").use();

    m_texture.loadFile("res/terrain.jpeg");

    model = glm::mat4(1.f);

    glGenVertexArrays(1, &m_array);
    glBindVertexArray(m_array);

    glGenBuffers(1, &m_posBuffer);
    glGenBuffers(1, &m_texCoordBuffer);
    glGenBuffers(1, &m_elementBuffer);

    //------------------------------------------------------------------------//

    glBindBuffer(GL_ARRAY_BUFFER, m_posBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positions.size()*3, &positions[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //------------------------------------------------------------------------//

    glBindBuffer(GL_ARRAY_BUFFER, m_texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * texCoords.size()*2, &texCoords[0], GL_STATIC_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    //------------------------------------------------------------------------//

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);

    vertexCount = 6;
}

void Mesh::update()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_posBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positions.size() * 3, &positions[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * texCoords.size() * 3, &texCoords[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);
}

void Mesh::addFace(std::array<Vector3f, 4> p_positions, std::array<Vector2f, 4> p_texCoords)
{
    positions.insert(positions.end(), p_positions.begin(), p_positions.end());
    texCoords.insert(texCoords.end(), p_texCoords.begin(), p_texCoords.end());

    int indexArr[] = {0, 1, 3, 1, 2, 3};
    indices.insert(indices.end(), std::begin(indexArr), std::end(indexArr));
}

void Mesh::render()
{
    ResourceManager::getShader("shader").use();
    ResourceManager::getShader("shader").setUniform("model", model);
    m_texture.bind();
    glBindVertexArray(m_array);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
    glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);
}