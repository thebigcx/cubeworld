#pragma once

#include "../Window.h"

class Game;

class State
{
public:
    State(Game& game) : m_pGame(&game) {}
    
    virtual ~State() {};
    
    virtual void handleInput(Window& window) = 0;
    virtual void handleEvent(Window& window) = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    
private:
    Game* m_pGame;
};
