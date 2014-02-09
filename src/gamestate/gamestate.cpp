#include "gamestate.h"


GameState::GameState(const std::string& name, GameState* parentGameState):
    State(name, parentGameState),
    m_parentGameState(parentGameState)
{
}

GameState* GameState::parentGameState() {
    return m_parentGameState;
}

void GameState::update(float deltaSec) {
    State::update(deltaSec);
}

void GameState::onEntered() {
    State::onEntered();
}

void GameState::onLeft() {
    State::onLeft();
}


