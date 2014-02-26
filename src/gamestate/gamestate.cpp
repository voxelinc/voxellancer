#include "gamestate.h"

#include <cassert>


GameState::GameState(const std::string& name, GameState* parent):
    State(name, parent),
    m_parentGameState(parent)
{
}

GameState* GameState::parentGameState() {
    return m_parentGameState;
}

const Scene& GameState::scene() const {
    assert(parentState());
    return m_parentGameState->scene();
}

const CameraHead& GameState::cameraHead() const {
    return m_parentGameState->cameraHead();
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


