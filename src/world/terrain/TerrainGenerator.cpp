#include "TerrainGenerator.h"

#include "../../util/math/Math.h"

BlockMap TerrainGenerator::generateChunk(int xPos, int zPos)
{
    BlockMap map;
    for (int x = 0 ; x < CHUNK_WIDTH ; x++)
    {
        for (int z = 0 ; z < CHUNK_WIDTH ; z++)
        {
            int height = Math::Random::generate(0, CHUNK_HEIGHT);
            for (int y = 0 ; y < height ; y++)
            {
                map[Chunk::getIndex(x, y, z)].setType(BlockType::Grass);
            }
        }
    }

    return map;
}