#include "Block.h"

#include <stdio.h>

Block::Block(Vector2i side, Vector2i top, Vector2i bottom)
{
    texCoordSide = side;
    texCoordTop = top;
    texCoordBottom = bottom;
};