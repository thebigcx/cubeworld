#include "Mesh.h"

Mesh::Mesh()
{
    ResourceManager::getShader("shader").use();

    model = glm::mat4(1.f);

    glGenVertexArrays(1, &m_array);
    glBindVertexArray(m_array);

    glGenBuffers(1, &m_posBuffer);
    glGenBuffers(1, &m_texCoordBuffer);
    glGenBuffers(1, &m_elementBuffer);

    //------------------------------------------------------------------------//

    glBindBuffer(GL_ARRAY_BUFFER, m_posBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //------------------------------------------------------------------------//

    glBindBuffer(GL_ARRAY_BUFFER, m_texCoordBuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    //------------------------------------------------------------------------//

    vertexCount = 6;
}

void Mesh::update()
{
    vertexCount = m_indices.size();

    // Send the updated data to the GPU

    glBindBuffer(GL_ARRAY_BUFFER, m_posBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_positions.size() * 3, &m_positions[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_texCoords.size() * 2, &m_texCoords[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_indices.size(), &m_indices[0], GL_STATIC_DRAW);
}

void Mesh::addFace(std::array<Vector3f, 4> p_positions, std::array<Vector2f, 4> p_texCoords, Vector3i p_blockPosition)
{
    int off = m_positions.size();
    int indexArr[] = {
        0 + off, 1 + off, 2 + off, 
        0 + off, 2 + off, 3 + off
    };

    m_indices.insert(m_indices.end(), std::begin(indexArr), std::end(indexArr));

    // Add the block position to the vertices
    std::array<Vector3f, 4> positions;
    for (int i = 0 ; i < p_positions.size() ; i++)
    {
        positions[i].x = p_positions[i].x + p_blockPosition.x;
        positions[i].y = p_positions[i].y + p_blockPosition.y;
        positions[i].z = p_positions[i].z + p_blockPosition.z;
    }

    m_positions.insert(m_positions.end(), positions.begin(), positions.end());
    m_texCoords.insert(m_texCoords.end(), p_texCoords.begin(), p_texCoords.end());

    
}

void Mesh::render()
{
    ResourceManager::getShader("shader").use();
    ResourceManager::getShader("shader").setUniform("model", model);

    ResourceManager::getTexture("terrainAtlas").bind();

    glBindVertexArray(m_array);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
    
    glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);
}

void Mesh::setPosition(Vector3f p_pos)
{
    model = glm::translate(glm::mat4(1.f), glm::vec3(p_pos.x, p_pos.y, p_pos.z));
}