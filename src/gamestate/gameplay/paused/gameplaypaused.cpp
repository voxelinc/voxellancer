#include "gameplaypaused.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "gamestate/game.h"
#include "gamestate/gameplay/gameplay.h"

#include "player.h"
#include "camera/camerahead.h"
#include "sound/soundmanager.h"

#include "camera/cameradolly.h"

GamePlayPaused::GamePlayPaused(GamePlay* gamePlay):
    GameState("GamePlay Paused", gamePlay),
    m_gamePlay(gamePlay),
    m_input(new GamePlayFreecamInput(gamePlay->player().cameraHead().cameraDolly())),
    m_continueTrigger(GLFW_KEY_P)
{

}

Trigger& GamePlayPaused::continueTrigger() {
    return m_continueTrigger;
}

void GamePlayPaused::update(float deltaSec) {
    GameState::update(deltaSec);
    m_continueTrigger.update(deltaSec);

    m_input->update(deltaSec);

    m_gamePlay->soundManager().setListener(m_input->position(), m_input->orientation());

    m_gamePlay->player().cameraHead().cameraDolly()->follow(m_input->position(), m_input->orientation(), deltaSec);
}

void GamePlayPaused::onEntered() {
    GameState::onEntered();
    m_gamePlay->soundManager().activate();
    m_gamePlay->player().cameraHead().cameraDolly()->setInertia(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
    m_input->setPosition(m_gamePlay->player().cameraHead().position());
    m_input->setOrientation(m_gamePlay->player().cameraHead().orientation());
}

void GamePlayPaused::onLeft() {
    GameState::onLeft();
    m_gamePlay->soundManager().deactivate();
}
