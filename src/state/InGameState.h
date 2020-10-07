#pragma once

#include "State.h"
#include "../player/Player.h"
#include "../world/World.h"

class InGameState : public State
{
public:
    InGameState(Game& game);
    
    void handleInput(Window& window) override;
    void handleEvent(Window& window) override;
    void update(float dt) override;
    void render() override;

private:
    World m_world;
    Player m_player;
};
