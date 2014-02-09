#include "inputhandler.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glow/glow.h>

#include "utils/tostring.h"
#include "utils/aimer.h"

#include "etc/windowmanager.h"

#include "worldobject/worldobject.h"
#include "player.h"
#include "ui/hud/hud.h"
#include "worldobject/ship.h"
#include "camera/cameradolly.h"


/*
* 360 gamepad assignment: (direction given for positive values)
* - A0: left stick right                        move right
* - A1: left stick up                           move forward
* - A2: left trigger (right trigger is [-1, 0]  -1 = gun trigger, +1 = rocket trigger
* - A3: right stick down(!)                     rotate down
* - A4: right stick right                       rotate up
*/

/*
* Button assignment
* B0: A
* B1: B
* B2: X
* B3: Y
* B4: left bumper               --previous target
* B5: right bumper              next target
* B6: back
* B7: start
* B8: left stick
* B9: right stick
*/

InputHandler::InputHandler(Player* player):
    m_player(player),
    m_hmd(nullptr),

    prop_deadzoneMouse("input.deadzoneMouse"),
    prop_deadzoneGamepad("input.deadzoneGamepad"),

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

    m_inputConfigurator(new InputConfigurator(&m_actions, &m_secondaryInputValues, &prop_deadzoneGamepad, &m_player->hud())),

    m_targetSelector(new TargetSelector(player))
{
    addActionsToVector();

    m_cursorMaxDistance = glm::min(WindowManager::instance()->resolution().width(), WindowManager::instance()->resolution().height()) / 2;

    m_mouseControl = false;
    m_lastfocus = glfwGetWindowAttrib(glfwGetCurrentContext(), GLFW_FOCUSED);

//    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    retrieveInputValues();
}

void InputHandler::setHMD(HMD* hmd) {
    m_hmd = hmd;
}

void InputHandler::resizeEvent(const unsigned int width, const unsigned int height){
	m_lastfocus = false; // through window resize everything becomes scrambled
}

/*
*    Check here for single-time key-presses, that you do not want fired multiple times, e.g. toggles
*    This only applies for menu events etc, for action events set the toggleAction attribute to true
*/
void InputHandler::keyCallback(int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        m_inputConfigurator->setLastPrimaryInput(InputMapping(InputType::Keyboard, key, 1, 0.0f));
    } else {
        m_inputConfigurator->setLastPrimaryInput(InputMapping());
    }

    if(action == GLFW_PRESS) {
        switch(key) {
            case GLFW_KEY_F10:
                if (glfwJoystickPresent(GLFW_JOYSTICK_1)) {
                    m_inputConfigurator->startConfiguration(false);
                }
            break;

            case GLFW_KEY_F11:
                m_inputConfigurator->startConfiguration(true);
                m_inputConfigurator->setLastPrimaryInput(InputMapping());
            break;

            case GLFW_KEY_SPACE:
                m_mouseControl = !m_mouseControl;
            break;
        }
    }
}


/*
*Check here for every-frame events, e.g. view & movement controls
*/
void InputHandler::update(float deltaSec) {
    if (glfwGetWindowAttrib(glfwGetCurrentContext(), GLFW_FOCUSED)) {
        if (m_lastfocus) {
            if (glfwJoystickPresent(GLFW_JOYSTICK_1)) {
                retrieveInputValues();
            }
            if (m_inputConfigurator->isConfiguring()) {
                m_inputConfigurator->update();
            } else {
                processUpdate();
                processMouseUpdate();
                processHMDUpdate();
            }
        }
    }
    m_lastfocus = glfwGetWindowAttrib(glfwGetCurrentContext(), GLFW_FOCUSED);
}

void InputHandler::retrieveInputValues() {
    m_secondaryInputValues.buttonCnt = 0;
    m_secondaryInputValues.axisCnt = 0;
    m_secondaryInputValues.buttonValues = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &m_secondaryInputValues.buttonCnt);
    m_secondaryInputValues.axisValues = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &m_secondaryInputValues.axisCnt);
}

void InputHandler::processUpdate() {
    processFireActions();
    processMoveActions();
    processRotateActions();
    processTargetSelectActions();
}

void InputHandler::processMouseUpdate() {
    // mouse handling
    double x, y;
    glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);

    bool pressed = glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

    m_player->hud().crossHair().setActionActive(pressed);

    if(glfwJoystickPresent(GLFW_JOYSTICK_1)) {
        /*Hack to center if gamepad is presentyy*/
        m_player->hud().crossHair().pointToLocalPoint(glm::vec3(0, 0, -1));
    } else {
        placeCrossHair(x, y);
    }

    if (pressed) {
        m_player->fire();
    }

    // spin
    float rel = 20;
    double dis = 0;
    float angX = 0;
    float angY = 0;

    if (m_mouseControl || glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        glm::vec3 rot;
        x = WindowManager::instance()->resolution().width() / 2 - (int)floor(x);
        y = WindowManager::instance()->resolution().height() / 2 - (int)floor(y);
        x = glm::min((double)m_cursorMaxDistance, x);
        y = glm::min((double)m_cursorMaxDistance, y);
        rot = glm::vec3(y, x, 0);
        rot /= m_cursorMaxDistance;

        if (glm::length(rot) < prop_deadzoneMouse) {
            rot = glm::vec3(0);
        }
        if (glm::length(rot) > 1) {
            rot = glm::normalize(rot);
        }
        m_player->rotate(rot);

    }
}

void InputHandler::processHMDUpdate() {
    if (m_hmd) {
        m_player->cameraDolly().cameraHead().setRelativeOrientation(m_hmd->orientation());
    } else {
        m_player->cameraDolly().cameraHead().setRelativeOrientation(glm::quat());
    }
}

void InputHandler::addActionsToVector() {
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

float InputHandler::getInputValue(ActionKeyMapping* action) {
    float inputValue = glm::max(getInputValue(action->primaryMapping.get()), getInputValue(action->secondaryMapping.get()));
    if (action->toggleAction) {
        if (inputValue) {
            if (action->toggleStatus) {
                inputValue = 0;
            }
            action->toggleStatus = true;
        } else {
            action->toggleStatus = false;
        }
    }
    return inputValue;
}

float InputHandler::getInputValue(InputMapping mapping) {
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

void InputHandler::processFireActions() {
    m_player->hud().crossHair().setActionActive(getInputValue(&fireAction) > 0.001);

    if (getInputValue(&fireAction)) {
        m_player->fire();
    }
    if (getInputValue(&rocketAction)) {
        if (m_player->playerShip()) {
            m_player->playerShip()->fireAtObject();
        }
    }
}

void InputHandler::processMoveActions() {
    m_player->move(glm::vec3(-getInputValue(&moveLeftAction), 0, 0));
    m_player->move(glm::vec3(getInputValue(&moveRightAction), 0, 0));
    m_player->move(glm::vec3(0, 0, -getInputValue(&moveForwardAction)));
    m_player->move(glm::vec3(0, 0, getInputValue(&moveBackwardAction)));
}

void InputHandler::processRotateActions() {
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
    if (glm::length(rot) > 1) {
        rot = glm::normalize(rot);
    }
    m_player->rotate(rot);
}

void InputHandler::processTargetSelectActions() {
    if (getInputValue(&selectNextAction)) {
        m_targetSelector->selectNextTarget();
    }
    if (getInputValue(&selectPreviousAction)) {
        m_targetSelector->selectPreviousTarget();
    }
}

void InputHandler::placeCrossHair(double winX, double winY) {
    int width, height;
    glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
    m_player->hud().setCrossHairOffset(glm::vec2((winX - (width/2))/(width/2), -(winY - (height/2))/(height/2)));
}

SecondaryInputValues::SecondaryInputValues() {
    buttonCnt = 0;
    axisCnt = 0;
    buttonValues = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCnt);
    axisValues = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axisCnt);
}
