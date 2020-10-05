#pragma once

#include <vector>
#include <string>

class Skybox
{
    public:
        Skybox();

        void render();

    private:
        unsigned int m_textureId;

        unsigned int m_vertices;
        unsigned int m_array;

        float m_positions[108] = {
            -1.f,  1.f, -1.f,
            -1.f, -1.f, -1.f,
             1.f, -1.f, -1.f,
             1.f, -1.f, -1.f,
             1.f,  1.f, -1.f,
            -1.f,  1.f, -1.f,

            -1.f, -1.f,  1.f,
            -1.f, -1.f, -1.f,
            -1.f,  1.f, -1.f,
            -1.f,  1.f, -1.f,
            -1.f,  1.f,  1.f,
            -1.f, -1.f,  1.f,

             1.f, -1.f, -1.f,
             1.f, -1.f,  1.f,
             1.f,  1.f,  1.f,
             1.f,  1.f,  1.f,
             1.f,  1.f, -1.f,
             1.f, -1.f, -1.f,

            -1.f, -1.f,  1.f,
            -1.f,  1.f,  1.f,
             1.f,  1.f,  1.f,
             1.f,  1.f,  1.f,
             1.f, -1.f,  1.f,
            -1.f, -1.f,  1.f,

            -1.f,  1.f, -1.f,
             1.f,  1.f, -1.f,
             1.f,  1.f,  1.f,
             1.f,  1.f,  1.f,
            -1.f,  1.f,  1.f,
            -1.f,  1.f, -1.f,

            -1.f, -1.f, -1.f,
            -1.f, -1.f,  1.f,
             1.f, -1.f, -1.f,
             1.f, -1.f, -1.f,
            -1.f, -1.f,  1.f,
             1.f, -1.f,  1.f
        };
};