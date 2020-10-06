#pragma once

#include "../world/chunk/Chunk.h"

class ChunkRenderer
{
    public:
        ChunkRenderer();

        void add(Mesh& mesh);

        void render(Chunk& p_chunk);
    
    private:
        std::vector<Mesh*> m_pMeshes;
};