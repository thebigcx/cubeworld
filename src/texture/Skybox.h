#pragma once

#include <vector>
#include <string>

class Skybox
{
    public:
        Skybox(std::vector<std::string> p_faces);

        void render();

    private:
        unsigned int m_textureId;

        unsigned int m_vertices;
        unsigned int m_array;

        float m_positions[108] = {
            -100.f,  100.f, -100.f,
            -100.f, -100.f, -100.f,
             100.f, -100.f, -100.f,
             100.f, -100.f, -100.f,
             100.f,  100.f, -100.f,
            -100.f,  100.f, -100.f,

            -100.f, -100.f,  100.f,
            -100.f, -100.f, -100.f,
            -100.f,  100.f, -100.f,
            -100.f,  100.f, -100.f,
            -100.f,  100.f,  100.f,
            -100.f, -100.f,  100.f,

             100.f, -100.f, -100.f,
             100.f, -100.f,  100.f,
             100.f,  100.f,  100.f,
             100.f,  100.f,  100.f,
             100.f,  100.f, -100.f,
             100.f, -100.f, -100.f,

            -100.f, -100.f,  100.f,
            -100.f,  100.f,  100.f,
             100.f,  100.f,  100.f,
             100.f,  100.f,  100.f,
             100.f, -100.f,  100.f,
            -100.f, -100.f,  100.f,

            -100.f,  100.f, -100.f,
             100.f,  100.f, -100.f,
             100.f,  100.f,  100.f,
             100.f,  100.f,  100.f,
            -100.f,  100.f,  100.f,
            -100.f,  100.f, -100.f,

            -100.f, -100.f, -100.f,
            -100.f, -100.f,  100.f,
             100.f, -100.f, -100.f,
             100.f, -100.f, -100.f,
            -100.f, -100.f,  100.f,
             100.f, -100.f,  100.f
        };
};