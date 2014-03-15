#include "gameplayrunning.h"

#include "gamestate/game.h"
#include "gamestate/gameplay/gameplay.h"
#include "gameplayrunninginput.h"

#include "camera/camerahead.h"
#include "camera/cameradolly.h"
#include "world/world.h"
#include "player.h"
#include "sound/soundmanager.h"


GamePlayRunning::GamePlayRunning(GamePlay* gamePlay):
    GameState("GamePlay Main", gamePlay),
    m_gamePlay(gamePlay),
    m_input(new GamePlayRunningInput(&gamePlay->player())),
    m_pauseTrigger(GLFW_KEY_P)
{

}

GamePlayRunningInput& GamePlayRunning::input() {
    return *m_input;
}

Trigger& GamePlayRunning::pauseTrigger() {
    return m_pauseTrigger;
}

void GamePlayRunning::update(float deltaSec) {
    GameState::update(deltaSec);
    m_pauseTrigger.update(deltaSec);

    m_input->update(deltaSec);

    World::instance()->update(deltaSec);

    m_gamePlay->player().update(deltaSec);

    m_gamePlay->soundManager().setListener(m_gamePlay->player().cameraHead().position(), m_gamePlay->player().cameraHead().orientation());
}

void GamePlayRunning::onEntered() {
    GameState::onEntered();
    m_gamePlay->soundManager().activate();
    m_gamePlay->player().cameraHead().cameraDolly()->setInertia(10.0f, 10.0f);
}

void GamePlayRunning::onLeft() {
    GameState::onLeft();
    m_gamePlay->soundManager().deactivate();
}

