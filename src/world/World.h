#pragma once

#include "chunk/ChunkManager.h"
#include "../render/ChunkRenderer.h"

class Player;

class World
{
    public:
        World();

        void render(ChunkRenderer& p_renderer);

        Chunk& getChunk(int x, int z);

        const std::vector<Chunk>& getChunks()
        {
            return m_chunkManager.getChunks();
        }
        bool chunkExists(int x, int z)
        {
            return m_chunkManager.chunkExists(x, z);
        }

        int getBlock(int x, int y, int z);

        void updateNeighbourChunks(int x, int z);
        void addChunkToUpdateList(int x, int z);
        void addChunkToUpdateList(Chunk& p_chunk);

        void update(Player& p_player);

    private:
        ChunkManager m_chunkManager;
};