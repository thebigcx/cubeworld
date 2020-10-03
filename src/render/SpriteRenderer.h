#pragma once

#include "../Sprite.h"

#include <vector>

class SpriteRenderer
{
    public:
        SpriteRenderer();

        void render();

        void add(Sprite& p_sprite);

    private:
        std::vector<Sprite*> m_pSprites;
};