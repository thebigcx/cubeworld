#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <array>

#include "Shader.h"
#include "Texture.h"
#include "resource/ResourceManager.h"
#include "util/Vector3.h"

class Mesh
{
    public:
        Mesh();

        void render();

        void update();

        void addFace(std::array<Vector3f, 4> p_positions, std::array<Vector2f, 4> p_texCoords);

        glm::mat4 model;
        
        int vertexCount = 0;

    private:
        unsigned int m_array, m_elementBuffer, m_posBuffer, m_texCoordBuffer;

        std::vector<Vector3f> positions;
        std::vector<Vector2f> texCoords;
        std::vector<int> indices;
};