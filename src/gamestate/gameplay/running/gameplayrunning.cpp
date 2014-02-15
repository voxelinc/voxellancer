#include "gameplayrunning.h"

#include <iostream>

#include "gamestate/game.h"
#include "gamestate/gameplay/gameplay.h"

#include "world/world.h"

#include "player.h"

#include "gameplayrunninginput.h"


GamePlayRunning::GamePlayRunning(GamePlay* gamePlay):
    GameState("GamePlay Main", gamePlay),
    m_gamePlay(gamePlay),
    m_input(new GamePlayRunningInput(&gamePlay->player()))
{

}

GamePlayRunningInput& GamePlayRunning::input() {
    return *m_input;
}

void GamePlayRunning::setPauseTrigger(const Trigger<GameState>& pauseTrigger) {
    m_input->setPauseTrigger(pauseTrigger);
}

void GamePlayRunning::update(float deltaSec) {
    GameState::update(deltaSec);

    m_input->update(deltaSec);

    World::instance()->update(deltaSec);

    m_gamePlay->player().update(deltaSec);

    m_gamePlay->soundManager().setListener(m_gamePlay->player().cameraPosition(), m_gamePlay->player().cameraOrientation());
}

void GamePlayRunning::onEntered() {
    GameState::onEntered();
    m_gamePlay->soundManager().activate();
}

void GamePlayRunning::onLeft() {
    GameState::onLeft();
    m_gamePlay->soundManager().deactivate();
}

