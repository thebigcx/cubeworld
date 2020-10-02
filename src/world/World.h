#pragma once

#include "chunk/ChunkManager.h"

class Player;

class World
{
    public:
        World();

        void render();

        Chunk& getChunk(int x, int z);

        int getBlock(int x, int y, int z);

        void addChunkToUpdateList(int x, int z);
        void addChunkToUpdateList(Chunk& p_chunk);

        void update(Player& p_player);

    private:
        ChunkManager m_chunkManager;
};