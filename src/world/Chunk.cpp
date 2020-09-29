#include "Chunk.h"

#include "../texture/TextureAtlas.h"
#include "BlockVertices.h"
#include "../util/math/Vector3.h"

Chunk::Chunk(Vector2i p_position)
: m_position(p_position)
{
    m_mesh.addFace(BlockVertices::front, TextureAtlas::getTexture(Vector2f(3, 0)), Vector3i(0, 0, 0));
    m_mesh.addFace(BlockVertices::left, TextureAtlas::getTexture(Vector2f(3, 0)), Vector3i(0, 0, 0));
    m_mesh.update();
}

void Chunk::render()
{
    m_mesh.render();
}