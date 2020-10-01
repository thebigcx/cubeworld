#include "TerrainGenerator.h"

#include "../../util/math/Math.h"

#include <fastnoise/FastNoiseLite.h>

BlockMap TerrainGenerator::generateChunk(int xPos, int zPos)
{
    BlockMap map;


    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);

    for (int x = 0 ; x < CHUNK_WIDTH ; x++)
    {
        for (int z = 0 ; z < CHUNK_WIDTH ; z++)
        {
            int height = noise.GetNoise((float)(x + (xPos * CHUNK_WIDTH)) * 2, (float)(z + (zPos * CHUNK_WIDTH)) * 2) * 32;
            height += 16;
            if (height < 0) height = 0;
            for (int y = 0 ; y < height ; y++)
            {
                // Set the block types
                int type = BlockType::Stone;
                if (y == height - 1)
                {
                    type = BlockType::Grass;
                }
                else if (y > height - 6)
                {
                    type = BlockType::Dirt;
                }
                
                map[Chunk::getIndex(x, y, z)].setType(type);
            }
        }
    }

    return map;
}