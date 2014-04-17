#include "gameplayfreecaminput.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "etc/contextprovider.h"
#include "etc/hmd/hmd.h"
#include "etc/hmd/hmdmanager.h"

#include "camera/camerahead.h"

#include "input/inputmapping.h"


GamePlayFreecamInput::GamePlayFreecamInput() :
    GamePlayInput(),

    m_cameraDolly(new CameraDolly()),

    prop_deadzoneMouse("input.deadzoneMouse"),
    prop_deadzoneGamepad("input.deadzoneGamepad"),

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

    prop_moveFactor("input.flycamMoveFactor", 1.0f),
    prop_rotateFactor("input.flycamRotateFactor", 0.5f),
    prop_mouseMultiplier("input.flycamMouseMultiplier", 1.0f)
{
    addActionsToVector();

    m_lastfocus = glfwGetWindowAttrib(glfwGetCurrentContext(), GLFW_FOCUSED);
    m_cursorMaxDistance = glm::min(ContextProvider::instance()->resolution().width(), ContextProvider::instance()->resolution().height()) / 2.0f;

    retrieveInputValues();

    m_cameraDolly->setInertia(0, 0);
}


void GamePlayFreecamInput::resizeEvent(const unsigned int width, const unsigned int height) {
    m_lastfocus = false; // through window resize the cursor position is scrambled
    m_cursorMaxDistance = glm::min(ContextProvider::instance()->resolution().width(), ContextProvider::instance()->resolution().height()) / 2.0f;
}

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


    m_cameraDolly->follow(m_position, m_orientation, deltaSec);
}


void GamePlayFreecamInput::applyUpdates() {
    // some actions can be triggered in different ways or multiple times
    // especially those done by the mouse
    // collect them and apply them here
    
    if (glm::length(m_moveUpdate) > 1.0f) {
        m_moveUpdate = glm::normalize(m_moveUpdate);
    }
    
    m_position += m_orientation * (m_moveUpdate * prop_moveFactor.get());
    m_moveUpdate = glm::vec3(0);

    m_orientation = m_orientation * glm::quat(m_rotateUpdate * prop_rotateFactor.get());
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

    glm::vec3 rot;
    x = ContextProvider::instance()->resolution().width() / 2 - x;
    y = ContextProvider::instance()->resolution().height() / 2 - y;
    rot = glm::vec3(y, x, 0);
    rot /= m_cursorMaxDistance;

    if (glm::length(rot) < prop_deadzoneMouse) {
        rot = glm::vec3(0);
    }
    m_rotateUpdate += rot * prop_mouseMultiplier.get();

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

CameraHead& GamePlayFreecamInput::cameraHead() {
    return m_cameraDolly->cameraHead();
}