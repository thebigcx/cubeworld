#pragma once

#include "../../util/math/Vector3.h"

#include <array>

struct BlockVertices
{
    public:

        static inline const std::array<Vector3f, 4> top = {
            Vector3f( 0.5f,  0.5f, -0.5f),
            Vector3f(-0.5f,  0.5f, -0.5f),
            Vector3f(-0.5f,  0.5f,  0.5f),
            Vector3f( 0.5f,  0.5f,  0.5f),
        };

        static inline const std::array<Vector3f, 4> bottom = {
            Vector3f( 0.5f, -0.5f,  0.5f),
            Vector3f(-0.5f, -0.5f,  0.5f),
            Vector3f(-0.5f, -0.5f, -0.5f),
            Vector3f( 0.5f, -0.5f, -0.5f),
        };

        static inline const std::array<Vector3f, 4> front = {
            Vector3f( 0.5f,  0.5f, 0.5f),
            Vector3f(-0.5f,  0.5f, 0.5f),
            Vector3f(-0.5f, -0.5f, 0.5f),
            Vector3f( 0.5f, -0.5f, 0.5f),
        };

        static inline const std::array<Vector3f, 4> back = {
            Vector3f(-0.5f,  0.5f, -0.5f),
            Vector3f( 0.5f,  0.5f, -0.5f),
            Vector3f( 0.5f, -0.5f, -0.5f),
            Vector3f(-0.5f, -0.5f, -0.5f),
        };

        static inline const std::array<Vector3f, 4> left = {
            Vector3f(-0.5f,  0.5f,  0.5f),
            Vector3f(-0.5f,  0.5f, -0.5f),
            Vector3f(-0.5f, -0.5f, -0.5f),
            Vector3f(-0.5f, -0.5f,  0.5f),
        };

        static inline const std::array<Vector3f, 4> right = {
            Vector3f( 0.5f,  0.5f, -0.5f),
            Vector3f( 0.5f,  0.5f,  0.5f),
            Vector3f( 0.5f, -0.5f,  0.5f),
            Vector3f( 0.5f, -0.5f, -0.5f),
        };
};