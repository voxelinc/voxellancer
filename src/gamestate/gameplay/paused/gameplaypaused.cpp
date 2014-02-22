#include "gameplaypaused.h"

#ifdef WIN32
#include <windows.h>
#endif
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "gamestate/game.h"
#include "gamestate/gameplay/gameplay.h"


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
}

void GamePlayPaused::onEntered() {
    GameState::onEntered();
}

void GamePlayPaused::onLeft() {
    GameState::onLeft();
}
