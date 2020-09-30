#include "Block.h"

#include <stdio.h>

Block::Block(Vector2i side, Vector2i top, Vector2i bottom, bool collide, bool trans)
{
    texCoordSide = side;
    texCoordTop = top;
    texCoordBottom = bottom;

    collidable = collide;
    transparent = trans;
};