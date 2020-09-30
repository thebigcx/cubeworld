#pragma once

#include "BlockType.h"
#include "Block.h"

#include <map>

struct BlockManager
{
    public:

        // TODO:  Refactor, maybe use JSONs or external binary files
        static inline const std::map<int, Block> blocks = {
            { BlockType::Grass, Block(Vector2i(3, 0), Vector2i(0, 0), Vector2i(2, 0), true, false) }
        };

        static Block getBlockData(BlockType type)
        {
            return blocks.find(type.getId())->second;
        }
};