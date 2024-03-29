#pragma once

#include "BlockType.h"
#include "Block.h"

#include <map>

struct BlockManager
{
    public:

        // TODO:  Refactor, maybe use JSONs or external binary files
        static inline const std::map<int, Block> blocks = {
            { BlockType::Air, Block(Vector2i(0, 0), Vector2i(0, 0), Vector2i(0, 0), false, true) },
            { BlockType::Grass, Block(Vector2i(3, 0), Vector2i(0, 0), Vector2i(2, 0), true, false) },
            { BlockType::Dirt, Block(Vector2i(2, 0), Vector2i(2, 0), Vector2i(2, 0), true, false) },
            { BlockType::Stone, Block(Vector2i(1, 0), Vector2i(1, 0), Vector2i(1, 0), true, false) },
            { BlockType::TNT, Block(Vector2i(8, 0), Vector2i(9, 0), Vector2i(10, 0), true, false) }
        };

        static Block getBlockData(BlockType type)
        {
            return blocks.find(type.getId())->second;
        }
};