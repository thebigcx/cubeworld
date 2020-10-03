#include "Skybox.h"

#include "../Image.h"
#include "../resource/ResourceManager.h"

#include <GL/glew.h>

Skybox::Skybox()
{
    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureId);

    auto createFace = [&](GLenum face, Image& img)
    {
        glTexImage2D(face,
                     0,
                     GL_RGBA,
                     img.getSize().x,
                     img.getSize().y,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     img.getPixels());
    };

    std::unordered_map<int, std::string> faces = {
        { GL_TEXTURE_CUBE_MAP_POSITIVE_X, "positive_x" },
        { GL_TEXTURE_CUBE_MAP_NEGATIVE_X, "negative_x" },
        { GL_TEXTURE_CUBE_MAP_POSITIVE_Y, "positive_y" },
        { GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, "negative_y" },
        { GL_TEXTURE_CUBE_MAP_POSITIVE_Z, "positive_z" },
        { GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, "negative_z" },
    };

    Image img;
    for (auto& path : faces)
    {
        std::string fullPath = std::string("res/skybox/skybox_").append(path.second).append(".png");
        img.loadFromFile(fullPath);
        createFace(path.first, img);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glGenVertexArrays(1, &m_array);
    glBindVertexArray(m_array);

    glGenBuffers(1, &m_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertices);

    glBufferData(GL_ARRAY_BUFFER, sizeof(m_positions), &m_positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Skybox::render()
{
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);

    ResourceManager::getShader("skybox").use();

    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureId);
    glBindVertexArray(m_array);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}