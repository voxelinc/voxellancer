#include "gameplayinput.h"

#include "GLFW/glfw3.h"

#include "gameplay.h"
#include "gameplayscene.h"


GamePlayInput::GamePlayInput(GamePlay& gamePlay):
    m_gamePlay(gamePlay)
{

}

void GamePlayInput::onResizeEvent(const unsigned int width, const unsigned int height) {

}

void GamePlayInput::onKeyEvent(int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_F) {
            m_gamePlay.setFreecamActive(!m_gamePlay.freecamActive());
        }

        if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9) {
            m_gamePlay.scene().setOutputBuffer(key - GLFW_KEY_1);
        }

        if (key == GLFW_KEY_T) {
            m_gamePlay.scene().setWorldTreeRendererEnabled(!m_gamePlay.scene().worldTreeRendererEnabled());
        }

        if (key >= GLFW_KEY_F1 && key <= GLFW_KEY_F7) {
            m_gamePlay.loadScenario(key - GLFW_KEY_F1);
        }
    }
}

void GamePlayInput::onMouseButtonEvent(int button, int action, int mods) {

}

void GamePlayInput::update(float deltaSec) {

}

