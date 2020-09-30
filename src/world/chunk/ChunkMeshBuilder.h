#pragma once

#include "../../Mesh.h"
#include "Chunk.h"

struct ChunkMeshBuilder
{
    public:
        
        static Mesh buildChunkMesh(Chunk& p_chunk);

    private:

        static bool shouldBuildFace(Chunk& p_chunk, Vector3i normal, Vector3i pos);
};