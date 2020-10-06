#pragma once

class MasterRenderer
{
    public:
        MasterRenderer();

    private:
        TextRenderer m_textRenderer;
        SpriteRenderer m_spriteRenderer;
        ChunkRenderer m_chunkRenderer;
}