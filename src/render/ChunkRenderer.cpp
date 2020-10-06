#include "ChunkRenderer.h"

ChunkRenderer::ChunkRenderer()
{

}

void ChunkRenderer::render(Chunk& p_chunk)
{
    ResourceManager::shaders.get("block").use();
    ResourceManager::shaders.get("block").setUniform("model", p_chunk.m_mesh.model);

    ResourceManager::textures.get("terrainAtlas").bind();

    glBindVertexArray(p_chunk.m_mesh.getVertexArray());
    
    glDrawElements(GL_TRIANGLES, p_chunk.m_mesh.vertexCount, GL_UNSIGNED_INT, 0);
}

void ChunkRenderer::add(Mesh& mesh)
{
    m_pMeshes.push_back(&mesh);
}