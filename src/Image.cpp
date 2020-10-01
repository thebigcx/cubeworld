#include "Image.h"

#include <stb_image/stb_image.h>

Image::Image()
{

}

Image::~Image()
{
    stbi_image_free(m_data);
}

void Image::setVerticalFlip(bool flip)
{
    m_flip = flip;
}

void Image::loadFromFile(std::string p_file)
{
    int width, height, nrChannels;

    if (m_flip)
    {
        stbi_set_flip_vertically_on_load(true);
    }
    else
    {
        stbi_set_flip_vertically_on_load(false);
    }
    
    m_data = stbi_load(p_file.c_str(), &width, &height, &nrChannels, 4);

    m_size.x = width;
    m_size.y = height;
}

const unsigned char* Image::getPixels() const
{
    return m_data;
}

Vector2u Image::getSize() const
{
    return m_size;
}
