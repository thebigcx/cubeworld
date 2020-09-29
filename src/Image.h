#pragma once

#include <string>

#include "util/math/Vector2.h"

class Image {
    public:
        Image();
        ~Image();

        void loadFromFile(std::string p_file);

        const unsigned char* getPixels() const;

        Vector2u getSize() const;

    private:
        unsigned char* m_data;

        Vector2u m_size;
};
