#include "gameplaynormalinput.h"

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

#include "camera/camerahead.h"
#include "camera/cameradolly.h"

#include "input/inputmapping.h"
#include "input/inputconfigurator.h"

#include "world/world.h"
#include "worldobject/worldobject.h"
#include "worldobject/worldobjectcomponents.h"
#include "worldobject/ship.h"

#include "player.h"

#include "ui/hud/hud.h"
#include "ui/targetselector.h"
#include "ui/hud/crosshair.h"



/*
 *  360 gamepad assignment: (direction given for positive values)
 *  - A0: left stick right                        move right
 *  - A1: left stick up                           move forward
 *  - A2: left trigger (right trigger is [-1, 0]  -1 = gun trigger, +1 = rocket trigger
 *  - A3: right stick down(!)                     rotate down
 *  - A4: right stick right                       rotate up
 */

/*
 *  Button assignment
 *  B0: A
 *  B1: B
 *  B2: X
 *  B3: Y
 *  B4: left bumper               --previous target
 *  B5: right bumper              next target
 *  B6: back
 *  B7: start
 *  B8: left stick
 *  B9: right stick
 */

GamePlayNormalInput::GamePlayNormalInput(GamePlay& gamePlay) :
    GamePlayInput(gamePlay),

    m_deadzoneMouse("input.deadzoneMouse"),
    m_deadzoneGamepad("input.deadzoneGamepad"),
    m_maxClickTime("input.maxClickTime"),

    fireAction("input.mappingFirePrimary", "input.mappingFireSecondary", "Fire"),
    rocketAction("input.mappingRocketPrimary", "input.mappingRocketSecondary", "Launch Rockets"),

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

    selectNextAction("input.mappingSelectNextPrimary", "input.mappingSelectNextSecondary", "Select Next Target", true),
    selectPreviousAction("input.mappingSelectPreviousPrimary", "input.mappingSelectPreviousSecondary", "Select Previous Target", true),

    m_secondaryInputValues(),
    m_actions(),

    m_inputConfigurator(new InputConfigurator(&m_actions, &m_secondaryInputValues, &m_deadzoneGamepad, &gamePlay.player().hud())),
    m_fireUpdate(false),
    m_rocketUpdate(false),
    m_moveUpdate(0),
    m_rotateUpdate(0),
    m_centerCrosshair(false),
    m_lastMousePos()
{
    addActionsToVector();

    m_cursorMaxDistance = glm::min(ContextProvider::instance()->resolution().width(), ContextProvider::instance()->resolution().height()) / 2;

    m_mouseControl = false;
    m_lastfocus = glfwGetWindowAttrib(glfwGetCurrentContext(), GLFW_FOCUSED);

    retrieveInputValues();
    m_currentTimePressed = 0;
}

void GamePlayNormalInput::onResizeEvent(const unsigned int width, const unsigned int height) {
    m_lastfocus = false; // through window resize everything becomes scrambled
    m_cursorMaxDistance = glm::min(ContextProvider::instance()->resolution().width(), ContextProvider::instance()->resolution().height()) / 2;
}

void GamePlayNormalInput::onKeyEvent(int key, int scancode, int action, int mods) {
    GamePlayInput::onKeyEvent(key, scancode, action, mods);

    if (action == GLFW_PRESS) {
        m_inputConfigurator->setLastInput(InputClass::Primary, InputMapping(InputType::Keyboard, key, 1, 0.0f));
    } else {
        m_inputConfigurator->setLastInput(InputClass::Primary, InputMapping());
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
                m_inputConfigurator->setLastInput(InputClass::Primary, InputMapping());
            break;

            case GLFW_KEY_SPACE:
                m_mouseControl = !m_mouseControl;
            break;
        }
    }
}


void GamePlayNormalInput::onMouseButtonEvent(int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        if (m_currentTimePressed > 0 && m_currentTimePressed < m_maxClickTime) {
            m_gamePlay.universe().player().hud().onClick(ClickType::Selection);
        }
        m_currentTimePressed = 0;
    }
}

void GamePlayNormalInput::update(float deltaSec) {
    if (glfwGetWindowAttrib(glfwGetCurrentContext(), GLFW_FOCUSED)) {
        if (m_lastfocus) {
            if (glfwJoystickPresent(GLFW_JOYSTICK_1)) {
                retrieveInputValues();
            }
            if (m_inputConfigurator->isConfiguring()) {
                m_inputConfigurator->update();
            } else {
                processUpdate();
                processMouseUpdate(deltaSec);
                applyUpdates();
                processHMDUpdate();
            }
        }
    }
    m_lastfocus = glfwGetWindowAttrib(glfwGetCurrentContext(), GLFW_FOCUSED);
}


void GamePlayNormalInput::applyUpdates() {
    // some actions can be triggered in different ways or multiple times
    // especially those done by the mouse
    // collect them and apply them here

    if (m_fireUpdate){
        m_gamePlay.universe().player().fire(); // fire checks for existence of ship
    }
    m_fireUpdate = false;

    if (m_rocketUpdate && m_gamePlay.universe().player().ship()) {
        m_gamePlay.universe().player().ship()->components().fireAtObject(m_gamePlay.universe().player().ship()->targetObject());
    }
    m_rocketUpdate = false;

    if (glm::length(m_moveUpdate) > 1.0f) {
        m_moveUpdate = glm::normalize(m_moveUpdate);
    }
    m_gamePlay.universe().player().move(m_moveUpdate);
    m_moveUpdate = glm::vec3(0);

    if (glm::length(m_rotateUpdate) > 1.0f) {
        m_rotateUpdate = glm::normalize(m_rotateUpdate);
    }
    m_gamePlay.universe().player().rotate(m_rotateUpdate);
    m_rotateUpdate = glm::vec3(0);
}


void GamePlayNormalInput::retrieveInputValues() {
    m_secondaryInputValues.buttonCnt = 0;
    m_secondaryInputValues.axisCnt = 0;
    m_secondaryInputValues.buttonValues = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &m_secondaryInputValues.buttonCnt);
    m_secondaryInputValues.axisValues = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &m_secondaryInputValues.axisCnt);
}

void GamePlayNormalInput::processUpdate() {
    processFireActions();
    processMoveActions();
    processRotateActions();
    processTargetSelectActions();
}

void GamePlayNormalInput::processMouseUpdate(float deltaSec) {
    // mouse handling
    double x, y;
    glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);

    bool pressed = glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

    m_gamePlay.universe().player().hud().crossHair().setActionActive(pressed);

    glm::vec2 mousePos(x, y);
    if (glm::length(m_lastMousePos - mousePos) > 0.01f) {
        m_centerCrosshair = false;
        m_lastMousePos = mousePos;
    }

    if (m_centerCrosshair) {
        m_gamePlay.universe().player().hud().crossHair().pointToLocalPoint(glm::vec3(0, 0, -1));
    } else {
        placeCrossHair(x, y);
    }

    if (pressed) {
        m_fireUpdate = true;
    }

    if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
        m_currentTimePressed += deltaSec;
    }

    if (m_mouseControl || glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS &&  m_maxClickTime < m_currentTimePressed) {
        glm::vec3 rot;
        x = ContextProvider::instance()->resolution().width() / 2 - (int)floor(x);
        y = ContextProvider::instance()->resolution().height() / 2 - (int)floor(y);
        x = glm::min((double)m_cursorMaxDistance, x);
        y = glm::min((double)m_cursorMaxDistance, y);
        rot = glm::vec3(y, x, 0);
        rot /= m_cursorMaxDistance;

        if (glm::length(rot) < m_deadzoneMouse) {
            rot = glm::vec3(0);
        }
        m_rotateUpdate += rot;

    }
}

void GamePlayNormalInput::processHMDUpdate() {
    if (HMDManager::instance()->hmd()) {
        m_gamePlay.universe().player().cameraHead().setRelativeOrientation(HMDManager::instance()->hmd()->orientation());
    } else {
       m_gamePlay.universe().player().cameraHead().setRelativeOrientation(glm::quat());
    }
}

void GamePlayNormalInput::addActionsToVector() {
    m_actions.push_back(&fireAction);
    m_actions.push_back(&rocketAction);
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
    m_actions.push_back(&selectNextAction);
    m_actions.push_back(&selectPreviousAction);
}

float GamePlayNormalInput::getInputValue(ActionKeyMapping* action) {
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

float GamePlayNormalInput::getInputValue(InputMapping mapping) {
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
            if (m_secondaryInputValues.axisCnt > mapping.index() && glm::abs(m_secondaryInputValues.axisValues[mapping.index()]) > m_deadzoneGamepad) {
                float relativeValue = m_secondaryInputValues.axisValues[mapping.index()] / mapping.maxValue();
                if (relativeValue > 0) {
                    m_centerCrosshair = true;
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

void GamePlayNormalInput::processFireActions() {
    m_gamePlay.universe().player().hud().crossHair().setActionActive(getInputValue(&fireAction) > 0.001);

    if (getInputValue(&fireAction)) {
        m_fireUpdate = true;
    }
    if (getInputValue(&rocketAction)) {
        m_rocketUpdate = true;
    }
}

void GamePlayNormalInput::processMoveActions() {
    glm::vec3 direction(
        getInputValue(&moveRightAction) - getInputValue(&moveLeftAction),
        0,
        getInputValue(&moveBackwardAction) - getInputValue(&moveForwardAction)
    );

    m_moveUpdate = direction;
}

void GamePlayNormalInput::processRotateActions() {
    glm::vec3 rot = glm::vec3(0);

    rot.x = getInputValue(&rotateUpAction)
        - getInputValue(&rotateDownAction);
    rot.y = getInputValue(&rotateLeftAction)
        - getInputValue(&rotateRightAction);
    rot.z = -getInputValue(&rotateClockwiseAction)
        + getInputValue(&rotateCClockwiseAction);

    if (glm::length(rot) < m_deadzoneGamepad) {
        rot = glm::vec3(0);
    }

    m_rotateUpdate += rot;
}

void GamePlayNormalInput::processTargetSelectActions() {
    if (getInputValue(&selectNextAction)) {
        m_gamePlay.universe().player().selectTarget(true);
    }
    if (getInputValue(&selectPreviousAction)) {
        m_gamePlay.universe().player().selectTarget(false);
    }
}

void GamePlayNormalInput::placeCrossHair(double winX, double winY) {
    int width, height;
    glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
    m_gamePlay.universe().player().hud().setCrossHairOffset(glm::vec2((winX - (width/2))/(width/2), -(winY - (height/2))/(height/2)));
}

