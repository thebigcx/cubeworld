#include "Chunk.h"

#include "../texture/TextureAtlas.h"

Chunk::Chunk(Vector2i p_position)
: m_position(p_position)
{
    std::array<Vector3f, 4> positions = {
        Vector3f( 0.5f,  0.5f, 0.5f),
        Vector3f(-0.5f,  0.5f, 0.5f),
        Vector3f(-0.5f, -0.5f, 0.5f),
        Vector3f( 0.5f, -0.5f, 0.5f),
    };

    m_mesh.addFace(positions, TextureAtlas::getTexture(Vector2f(3, 0)));
    m_mesh.update();
}

void Chunk::render()
{
    m_mesh.render();
}