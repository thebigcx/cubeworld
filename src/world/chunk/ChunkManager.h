#pragma once

#include <vector>

#include "Chunk.h"

class World;

class ChunkManager
{
    public:
        ChunkManager(World& p_world);

        std::vector<Chunk>& getChunks()
        {
            return m_chunks;
        }

        Chunk& loadChunk(int x, int z);

        bool chunkExists(int x, int z);

        void addChunkToUpdateBatch(int x, int z);
        void addChunkToUpdateBatch(Chunk& p_chunk);

        const Chunk& getChunk(int x, int z);

        void update();

        int getIndex(int x, int z);

    private:
        std::vector<Chunk> m_chunks;
        std::vector<Chunk*> m_chunkUpdateBatch;

        World* m_world;
};