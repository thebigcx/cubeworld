#pragma once

#include "../../util/math/Vector2.h"

class Block
{
    public:
        bool collidable = true;
        bool transparent = false;

        Vector2i texCoordSide;
        Vector2i texCoordTop;
        Vector2i texCoordBottom;

        Block(Vector2i side, Vector2i top, Vector2i bottom);
};