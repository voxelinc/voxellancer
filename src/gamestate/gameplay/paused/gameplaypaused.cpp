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
    m_continueTrigger(GLFW_KEY_P)
{

}

Trigger& GamePlayPaused::continueTrigger() {
    return m_continueTrigger;
}

void GamePlayPaused::update(float deltaSec) {
    GameState::update(deltaSec);
    m_continueTrigger.update(deltaSec);

    m_gamePlay->soundManager().setListener(m_gamePlay->player().cameraHead().cameraDolly()->position(), 
        m_gamePlay->player().cameraHead().cameraDolly()->orientation());
}

void GamePlayPaused::onEntered() {
    GameState::onEntered();
    m_gamePlay->soundManager().activate();
}

void GamePlayPaused::onLeft() {
    GameState::onLeft();
    m_gamePlay->soundManager().deactivate();
}
