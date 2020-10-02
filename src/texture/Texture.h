#pragma once

#include <GL/glew.h>
#include <stb_image/stb_image.h>

#include <string>

#include "../util/math/Vector2.h"

class Texture {
    public:
        Texture();

        ~Texture();

        void bind();

        bool loadFile(const std::string& p_file);

        void setSmooth(bool p_smooth = true);
        bool isSmooth() const;

        void setRepeated(bool p_repeated = true);
        bool isRepeated() const;

        Vector2u getSize() const;

    private:
        unsigned int m_texture;

        bool m_smooth = false;
        bool m_repeated = false;
        bool m_mipmapped = false;

        Vector2u m_size;
};
