#include "SpriteRenderer.h"

#include "../resource/ResourceManager.h"

SpriteRenderer::SpriteRenderer()
{

}

void SpriteRenderer::add(Sprite& p_sprite)
{
    m_pSprites.push_back(&p_sprite);
}

void SpriteRenderer::render()
{
    ResourceManager::shaders.get("ortho").use();
    unsigned int tex = 0; // Reduce texture bind() calls
    // TODO: one draw call for all sprites
    for (auto sprite : m_pSprites)
    {
        if (sprite->getTexture()->getId() != tex)
        {
            sprite->getTexture()->bind();
        }

        tex = sprite->getTexture()->getId();

        ResourceManager::shaders.get("ortho").setUniform("model", sprite->getTransformationMatrix());
        
        glBindVertexArray(sprite->getVertices());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}