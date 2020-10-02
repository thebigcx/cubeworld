#include "ChunkMeshBuilder.h"

#include "../block/BlockManager.h"
#include "../block/BlockVertices.h"
#include "../../texture/TextureAtlas.h"

Mesh ChunkMeshBuilder::buildChunkMesh(Chunk& p_chunk)
{
    Mesh mesh;

    for (int x = 0 ; x < CHUNK_WIDTH ; x++)
    for (int y = 0 ; y < CHUNK_HEIGHT ; y++)
    for (int z = 0 ; z < CHUNK_WIDTH ; z++)
    {
        auto block = BlockManager::getBlockData(p_chunk.getBlock(x, y, z));
        if (block.transparent)
        {
            continue; // Discard a transparent block's faces
        }
        auto sideCoords = TextureAtlas::getTexture(block.texCoordSide);
        Vector3i pos(x, y, z);

        if (shouldBuildFace(p_chunk, Vector3i(0, 0, 1), pos))
        {
            mesh.addFace(BlockVertices::front, sideCoords, pos);
        }
                
        if (shouldBuildFace(p_chunk, Vector3i(0, 0, -1), pos))
        {
            mesh.addFace(BlockVertices::back, sideCoords, pos);
        }
                
        if (shouldBuildFace(p_chunk, Vector3i(-1, 0, 0), pos))
        {
            mesh.addFace(BlockVertices::left, sideCoords, pos);
        }
                
        if (shouldBuildFace(p_chunk, Vector3i(1, 0, 0), pos))
        {
            mesh.addFace(BlockVertices::right, sideCoords, pos);
        }

        if (shouldBuildFace(p_chunk, Vector3i(0, 1, 0), pos))
        {
            mesh.addFace(BlockVertices::top, TextureAtlas::getTexture(block.texCoordTop), pos);
        }

        if (shouldBuildFace(p_chunk, Vector3i(0, -1, 0), pos))
        {
            mesh.addFace(BlockVertices::bottom, TextureAtlas::getTexture(block.texCoordBottom), pos);
        }
    }
    
    mesh.update();

    return mesh;
}


bool ChunkMeshBuilder::shouldBuildFace(Chunk& p_chunk, Vector3i normal, Vector3i pos)
{
    Vector3i adj = pos + normal;
    
    if (adj.y < 0 || adj.y > CHUNK_HEIGHT)
    {
        return false;
    }

    // TEMPORARY
    if (adj.x < 0 || adj.z < 0 || adj.x > CHUNK_WIDTH || adj.z > CHUNK_WIDTH)
    {
        return true;
    }
    
    if (p_chunk.getBlock(adj.x, adj.y, adj.z) == BlockType::Air)
    {
        return true;
    }

    return false;
}