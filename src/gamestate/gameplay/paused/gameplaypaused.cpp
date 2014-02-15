#include "gameplaypaused.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gamestate/game.h"
#include "gamestate/gameplay/gameplay.h"


GamePlayPaused::GamePlayPaused(GamePlay* gamePlay):
    GameState("GamePlay Paused", gamePlay),
    m_gamePlay(gamePlay)
{

}

void GamePlayPaused::setContinueTrigger(const Trigger<GameState>& continueTrigger) {
    m_continueTrigger = continueTrigger;
}

void GamePlayPaused::update(float deltaSec) {
    GameState::update(deltaSec);

    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_C) == GLFW_PRESS) {
        m_continueTrigger.trigger();
    }
}

void GamePlayPaused::onEntered() {
    GameState::onEntered();
}

void GamePlayPaused::onLeft() {
    GameState::onLeft();
}
