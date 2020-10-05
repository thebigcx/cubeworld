#include "TerrainGenerator.h"

#include "../../util/math/Math.h"

#include "../../util/math/noise/OpenSimplexNoise.hh"

BlockMap TerrainGenerator::generateChunk(int xPos, int zPos, long seed)
{
    BlockMap map;
    OSN::Noise<2> noise(seed);

    for (int x = 0 ; x < CHUNK_WIDTH ; x++)
    for (int z = 0 ; z < CHUNK_WIDTH ; z++)
    {
        float noiseX = (x + (xPos * CHUNK_WIDTH)) * 0.05f;
        float noiseZ = (z + (zPos * CHUNK_WIDTH)) * 0.05f;

        float octave1 = 1.f * noise.eval(noiseX * 1, noiseZ * 1) + 1;
        float octave2 = 0.5f * noise.eval(noiseX * 2, noiseZ * 2) + 1;
        float octave3 = 0.25f * noise.eval(noiseX * 4, noiseZ * 4) + 1;
        float octave4 = 0.125f * noise.eval(noiseX * 8, noiseZ * 8) + 1;

        int height = pow(octave1 + octave2 + octave3 + octave4, 1.5) * 2;
        height += CHUNK_HEIGHT * 0.5f;

        if (height < 0) height = 0;
        if (height > CHUNK_HEIGHT) height = CHUNK_HEIGHT;

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

    OSN::Noise<3> caveNoise;

    for (int x = 0 ; x < CHUNK_WIDTH ; x++)
    for (int y = 0 ; y < CHUNK_HEIGHT ; y++)
    for (int z = 0 ; z < CHUNK_WIDTH ; z++)
    {
        float noiseX = (x + (xPos * CHUNK_WIDTH)) * 0.2f;
        float noiseY = y * 0.2f;
        float noiseZ = (z + (zPos * CHUNK_WIDTH)) * 0.2f;
        float val = caveNoise.eval(noiseX, noiseY, noiseZ);

        if (val > 0.3)
        {
            map[Chunk::getIndex(x, y, z)].setType(BlockType::Air);
        }
    }

    return map;
}