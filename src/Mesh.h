#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <array>

#include "shader/Shader.h"
#include "texture/Texture.h"
#include "resource/ResourceManager.h"
#include "util/math/Vector3.h"

class Mesh
{
    public:
        Mesh();

        void render();

        void update();

        void addFace(std::array<Vector3f, 4> p_positions, std::array<Vector2f, 4> p_texCoords, Vector3i p_blockPosition);

        glm::mat4 model;
        
        int vertexCount = 0;

        void setPosition(Vector3f p_pos);

    private:
        unsigned int m_array, m_elementBuffer, m_posBuffer, m_texCoordBuffer;

        std::vector<Vector3f> m_positions;
        std::vector<Vector2f> m_texCoords;
        std::vector<int> m_indices;
};