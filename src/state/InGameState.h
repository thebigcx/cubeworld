#pragma once

#include "State.h"

class InGameState : public State
{
public:
    InGameState(Game& game);
    
    void handleInput(Window& window) override;
    void handleEvent(Window& window) override;
    void update(float dt) override;
    void render() override;
};
