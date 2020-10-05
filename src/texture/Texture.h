#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <stb_image/stb_image.h>

#include <string>

#include "../util/math/Vector2.h"

class Texture {
    public:
        Texture();

        ~Texture();

        void bind() const;

        bool loadFile(const std::string& p_file);

        void setSmooth(bool p_smooth = true);
        bool isSmooth() const;

        void setRepeated(bool p_repeated = true);
        bool isRepeated() const;

        glm::uvec2 getSize() const;

        unsigned int getId() const
        {
            return m_texture;
        }

    private:
        unsigned int m_texture;

        bool m_smooth = false;
        bool m_repeated = false;
        bool m_mipmapped = false;

        glm::uvec2 m_size;
};
