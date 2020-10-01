#include "Texture.h"

#include "../Image.h"

Texture::Texture()
{

}

Texture::~Texture()
{
    //glDeleteTextures(1, &m_texture); // Don't need to - textures should always be global, as to save memory
}

bool Texture::loadFile(std::string p_file)
{
    glGenTextures(1, &m_texture);

    glBindTexture(GL_TEXTURE_2D, m_texture);

    Image image;
    image.setVerticalFlip(true);
    image.loadFromFile(p_file);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if (image.getPixels())
    {
        glTexImage2D(GL_TEXTURE_2D,      // Type of texture
                     0,                  // Level of detail (0 default)
                     GL_RGBA,            // Format of texture
                     image.getSize().x,  // Height
                     image.getSize().y,  // Width
                     0,                  // Border (must be 0)
                     GL_RGBA,            // Format of image
                     GL_UNSIGNED_BYTE,   // Type of pixel data (uint8_t)
                     image.getPixels()); // Pixel data

        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        m_mipmapped = true;
    }
    else
    {
        printf("Failed to load texture.\n");
        return false;
    }

    m_size.x = image.getSize().x;
    m_size.y = image.getSize().y;

    return true;
}

void Texture::setSmooth(bool p_smooth)
{
    this->bind();

    auto filter = p_smooth ? GL_NEAREST : GL_LINEAR;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

    m_smooth = p_smooth;
}

bool Texture::isSmooth() const
{
    return m_smooth;
}

void Texture::setRepeated(bool p_repeated)
{
    this->bind();

    auto repeat = p_repeated ? GL_REPEAT : GL_CLAMP_TO_EDGE;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeat);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeat);

    m_repeated = p_repeated;
}

bool Texture::isRepeated() const
{
    return m_repeated;
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

Vector2u Texture::getSize() const
{
    return m_size;
}
