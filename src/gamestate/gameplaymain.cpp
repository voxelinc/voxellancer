#include "gameplaymain.h"

#include <iostream>

#include "world/world.h"

#include "player.h"

#include "game.h"
#include "gameplay.h"


GamePlayMain::GamePlayMain(GamePlay* gamePlay):
    GameState("GamePlay Main", gamePlay),
    m_gamePlay(gamePlay),
    m_inputHandler(&gamePlay->player())
{

}

GamePlayMainInput& GamePlayMain::inputHandler() {
    return m_inputHandler;
}

void GamePlayMain::setPauseTrigger(const Trigger<GameState>& pauseTrigger) {
    m_inputHandler.setPauseTrigger(pauseTrigger);
}

void GamePlayMain::update(float deltaSec) {
    GameState::update(deltaSec);

    m_inputHandler.update(deltaSec);

    World::instance()->update(deltaSec);

    m_gamePlay->player().update(deltaSec);

    m_gamePlay->soundManager().setListener(m_gamePlay->player().cameraPosition(), m_gamePlay->player().cameraOrientation());
}

void GamePlayMain::onEntered() {
    GameState::onEntered();
    m_inputHandler.setHMD(m_gamePlay->game()->hmdManager().hmd());
    m_gamePlay->soundManager().activate();
}

void GamePlayMain::onLeft() {
    GameState::onLeft();
    m_gamePlay->soundManager().deactivate();
}

