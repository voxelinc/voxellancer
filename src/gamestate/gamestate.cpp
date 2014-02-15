#include "gamestate.h"

#include <cassert>


GameState::GameState(const std::string& name, GameState* parent):
    StateTemplate(name, this, parent)
{
}

const Scene& GameState::scene() const {
    assert(parentState());
    return parentState()->scene();
}

const CameraHead& GameState::cameraHead() const {
    return parentState()->cameraHead();
}

void GameState::update(float deltaSec) {
    StateTemplate::update(deltaSec);
}

void GameState::onEntered() {
    StateTemplate::onEntered();
}

void GameState::onLeft() {
    StateTemplate::onLeft();
}


