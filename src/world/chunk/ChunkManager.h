#pragma once

#include <vector>

#include "Chunk.h"


class World;
class Player;

class ChunkManager
{
    public:
        ChunkManager(World& p_world, long seed);

        std::vector<Chunk>& getChunks()
        {
            return m_chunks;
        }

        Chunk& loadChunk(int x, int z);

        void setSeed(long seed)
        {
            m_seed = seed;
        }

        bool chunkExists(int x, int z);

        void updateNeighbourChunks(int x, int z);
        void addChunkToUpdateBatch(int x, int z);
        void addChunkToUpdateBatch(Chunk& p_chunk);

        const Chunk& getChunk(int x, int z);

        void update(Player& p_player);

        int getIndex(int x, int z);

    private:
        std::vector<Chunk> m_chunks;
        std::vector<Chunk*> m_chunkUpdateBatch;

        World* m_world;

        Vector2i m_lastGenChunk;
        Vector2i m_lastPlayerPos;

        long m_seed = 0l;
};