#pragma once

#include "texture/Texture.h"
#include "util/math/Vector3.h"
#include "Transformable.h"

#include <glm/glm.hpp>

#include <array>

class Sprite : public Transformable
{
    public:
        Sprite(const Texture& p_texture);

        unsigned int getVertices()
        {
            return m_vertArray;
        }

        const Texture* getTexture()
        {
            return m_pTexture;
        }

    private:
        const Texture* m_pTexture;

        unsigned int m_vertArray;
        unsigned int m_elementBuf, m_texCoordBuf, m_positionBuf;

        static inline const float m_positions[8] = {
            1.f, 1.f,
            0.f, 1.f,
            0.f, 0.f,
            1.f, 0.f
        };

        static inline const int m_indices[6] = {
            0, 1, 2,
            0, 2, 3
        };

        static inline const float m_texCoords[8] = {
            1.f, 1.f,
            1.f, 0.f,
            0.f, 0.f,
            0.f, 1.f
        };
};