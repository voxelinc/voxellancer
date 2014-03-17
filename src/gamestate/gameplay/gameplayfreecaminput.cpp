#include "gameplayfreecaminput.h"

#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "etc/contextprovider.h"
#include "etc/hmd/hmd.h"
#include "etc/hmd/hmdmanager.h"

#include "gamestate/gamestate.h"

#include "utils/tostring.h"
#include "utils/aimer.h"

#include "camera/camerahead.h"
#include "camera/cameradolly.h"
#include "etc/hmd/hmd.h"
#include "input/inputmapping.h"
#include "ui/hud/hud.h"
#include "ui/inputconfigurator.h"


GamePlayFreecamInput::GamePlayFreecamInput(CameraDolly* cameraDolly):
    m_cameraDolly(cameraDolly),

    prop_deadzoneMouse("input.deadzoneMouse"),
    prop_deadzoneGamepad("input.deadzoneGamepad"),
    prop_maxClickTime("input.maxClickTime"),

    moveLeftAction("input.mappingMoveLeftPrimary", "input.mappingMoveLeftSecondary", "Move Left"),
    moveRightAction("input.mappingMoveRightPrimary", "input.mappingMoveRightSecondary", "Move Right"),
    moveForwardAction("input.mappingMoveForwardPrimary", "input.mappingMoveForwardSecondary", "Move Forward"),
    moveBackwardAction("input.mappingMoveBackwardPrimary", "input.mappingMoveBackwardSecondary", "Move Backward"),

    rotateLeftAction("input.mappingRotateLeftPrimary", "input.mappingRotateLeftSecondary", "Rotate Left"),
    rotateRightAction("input.mappingRotateRightPrimary", "input.mappingRotateRightSecondary", "Rotate Right"),
    rotateUpAction("input.mappingRotateUpPrimary", "input.mappingRotateUpSecondary", "Rotate Up"),
    rotateDownAction("input.mappingRotateDownPrimary", "input.mappingRotateDownSecondary", "Rotate Down"),
    rotateClockwiseAction("input.mappingRotateClockwisePrimary", "input.mappingRotateClockwiseSecondary", "Rotate Clockwise"),
    rotateCClockwiseAction("input.mappingRotateCClockwisePrimary", "input.mappingRotateCClockwiseSecondary", "Rotate CounterClockwise"),

    m_secondaryInputValues(),
    m_actions(),

    m_moveUpdate(0),
    m_rotateUpdate(0),

    m_moveFactor(1),
    m_rotateFactor(0.05f)
{
    addActionsToVector();

    m_lastfocus = glfwGetWindowAttrib(glfwGetCurrentContext(), GLFW_FOCUSED);
//    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    retrieveInputValues();
    m_currentTimePressed = 0;
}

/*
void GamePlayFreecamInput::resizeEvent(const unsigned int width, const unsigned int height) {
    m_lastfocus = false; // through window resize everything becomes scrambled
}*/

/*
*    Check here for single-time key-presses, that you do not want fired multiple times, e.g. toggles
*    This only applies for menu events etc, for action events set the toggleAction attribute to true
*/
/*void GamePlayFreecamInput::keyCallback(int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        m_inputConfigurator->setLastInput(InputMapping(InputType::Keyboard, key, 1, 0.0f), InputClass::Primary);
    } else {
        m_inputConfigurator->setLastInput(InputMapping(), InputClass::Primary);
    }

    if(action == GLFW_PRESS) {
        switch(key) {
            case GLFW_KEY_F10:
                if (glfwJoystickPresent(GLFW_JOYSTICK_1)) {
                    m_inputConfigurator->startConfiguration(InputClass::Secondary);
                }
            break;

            case GLFW_KEY_F11:
                m_inputConfigurator->startConfiguration(InputClass::Primary);
                m_inputConfigurator->setLastInput(InputMapping(), InputClass::Primary);
            break;

            case GLFW_KEY_SPACE:
                m_mouseControl = !m_mouseControl;
            break;
        }
    }
}


void GamePlayFreecamInput::mouseButtonCallback(int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        if (m_currentTimePressed > 0 && m_currentTimePressed < prop_maxClickTime) {
            m_player->hud().onClick(ClickType::Selection);
        } else {
        }
        m_currentTimePressed = 0;
    }
}*/


/*
*Check here for every-frame events, e.g. view & movement controls
*/
void GamePlayFreecamInput::update(float deltaSec) {
    if (glfwGetWindowAttrib(glfwGetCurrentContext(), GLFW_FOCUSED)) {
        if (m_lastfocus) {
            if (glfwJoystickPresent(GLFW_JOYSTICK_1)) {
                retrieveInputValues();
            }

            processUpdate();
            processMouseUpdate(deltaSec);
            applyUpdates();
            processHMDUpdate();
        }
    }
    m_lastfocus = glfwGetWindowAttrib(glfwGetCurrentContext(), GLFW_FOCUSED);
}


void GamePlayFreecamInput::applyUpdates() {
    // some actions can be triggered in different ways or multiple times
    // especially those done by the mouse
    // collect them and apply them here
    
    if (glm::length(m_moveUpdate) > 1.0f) {
        m_moveUpdate = glm::normalize(m_moveUpdate);
    }
    
    m_position += m_orientation * (m_moveUpdate * m_moveFactor);
    m_moveUpdate = glm::vec3(0);

    if (glm::length(m_rotateUpdate) > 1.0f) {
        m_rotateUpdate = glm::normalize(m_rotateUpdate);
    }
    m_orientation = m_orientation * glm::quat(m_rotateUpdate * m_rotateFactor);
    m_rotateUpdate = glm::vec3(0);
}


void GamePlayFreecamInput::retrieveInputValues() {
    m_secondaryInputValues.buttonCnt = 0;
    m_secondaryInputValues.axisCnt = 0;
    m_secondaryInputValues.buttonValues = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &m_secondaryInputValues.buttonCnt);
    m_secondaryInputValues.axisValues = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &m_secondaryInputValues.axisCnt);
}

void GamePlayFreecamInput::processUpdate() {
    processMoveActions();
    processRotateActions();
}

void GamePlayFreecamInput::processMouseUpdate(float deltaSec) {
    // mouse handling
    double x, y;
    glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
    
    if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
        m_currentTimePressed += deltaSec;
    }

    glm::vec3 rot;
    x = ContextProvider::instance()->resolution().width() / 2 - (int)floor(x);
    y = ContextProvider::instance()->resolution().height() / 2 - (int)floor(y);
    //x = glm::min((double)m_cursorMaxDistance, x);
    //y = glm::min((double)m_cursorMaxDistance, y);
    rot = glm::vec3(y, x, 0);
    //rot /= m_cursorMaxDistance;

    if (glm::length(rot) < prop_deadzoneMouse) {
        rot = glm::vec3(0);
    }
    m_rotateUpdate += rot;

    x = ContextProvider::instance()->resolution().width() / 2;
    y = ContextProvider::instance()->resolution().height() / 2;
    glfwSetCursorPos(glfwGetCurrentContext(), x, y);
}

void GamePlayFreecamInput::processHMDUpdate() {
    if (HMDManager::instance()->hmd()) {
        m_cameraDolly->cameraHead().setRelativeOrientation(HMDManager::instance()->hmd()->orientation());
    } else {
        m_cameraDolly->cameraHead().setRelativeOrientation(glm::quat());
    }
}

void GamePlayFreecamInput::addActionsToVector() {
    m_actions.push_back(&moveLeftAction);
    m_actions.push_back(&moveRightAction);
    m_actions.push_back(&moveForwardAction);
    m_actions.push_back(&moveBackwardAction);
    m_actions.push_back(&rotateLeftAction);
    m_actions.push_back(&rotateRightAction);
    m_actions.push_back(&rotateUpAction);
    m_actions.push_back(&rotateDownAction);
    m_actions.push_back(&rotateClockwiseAction);
    m_actions.push_back(&rotateCClockwiseAction);
}

float GamePlayFreecamInput::getInputValue(ActionKeyMapping* action) {
    float inputValue = glm::max(getInputValue(action->mapping(InputClass::Primary)), getInputValue(action->mapping(InputClass::Secondary)));
    if (action->toggleAction()) {
        if (inputValue) {
            if (action->toggleStatus()) {
                inputValue = 0;
            }
            action->setToggleStatus(true);
        } else {
            action->setToggleStatus(false);
        }
    }
    return inputValue;
}

float GamePlayFreecamInput::getInputValue(InputMapping mapping) {
    switch (mapping.type()) {
        case InputType::None:
            return 0;
        case InputType::Keyboard:
            if (glfwGetKey(glfwGetCurrentContext(), mapping.index()) == GLFW_PRESS) {
                return 1;
            } else {
                return 0;
            }
        case InputType::GamePadKey:
            if (m_secondaryInputValues.buttonCnt > mapping.index() && m_secondaryInputValues.buttonValues[mapping.index()] == GLFW_PRESS) {
                return 1;
            } else {
                return 0;
            }
        case InputType::GamePadAxis:
            if (m_secondaryInputValues.axisCnt > mapping.index() && glm::abs(m_secondaryInputValues.axisValues[mapping.index()]) > prop_deadzoneGamepad) {
                float relativeValue = m_secondaryInputValues.axisValues[mapping.index()] / mapping.maxValue();
                if (relativeValue > 0) {
                    return glm::min(relativeValue, 1.0f);
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        default: return 0;
    }
}

void GamePlayFreecamInput::processMoveActions() {
    glm::vec3 direction(
        getInputValue(&moveRightAction) - getInputValue(&moveLeftAction),
        0,
        getInputValue(&moveBackwardAction) - getInputValue(&moveForwardAction)
    );

    m_moveUpdate = direction;
}

void GamePlayFreecamInput::processRotateActions() {
    glm::vec3 rot = glm::vec3(0);

    rot.x = getInputValue(&rotateUpAction)
        - getInputValue(&rotateDownAction);
    rot.y = getInputValue(&rotateLeftAction)
        - getInputValue(&rotateRightAction);
    rot.z = -getInputValue(&rotateClockwiseAction)
        + getInputValue(&rotateCClockwiseAction);

    if (glm::length(rot) < prop_deadzoneGamepad) {
        rot = glm::vec3(0);
    }

    m_rotateUpdate += rot;
}

const glm::vec3& GamePlayFreecamInput::position() {
    return m_position;
}

const glm::quat& GamePlayFreecamInput::orientation() {
    return m_orientation;
}

void GamePlayFreecamInput::setPosition(const glm::vec3& position) {
    m_position = position;
}

void GamePlayFreecamInput::setOrientation(const glm::quat& orientation) {
    m_orientation = orientation;

    double x = ContextProvider::instance()->resolution().width() / 2;
    double y = ContextProvider::instance()->resolution().height() / 2;
    glfwSetCursorPos(glfwGetCurrentContext(), x, y);
}