#include "inputhandler.h"

#include <glm/glm.hpp>
#include <glow/glow.h>

#include "voxeleffect/voxelexplosiongenerator.h"

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


InputHandler::InputHandler(GLFWwindow *window, Player* player, Camera *camera) :
m_window(window),
m_player(player),
m_camera(camera),
prop_deadzoneMouse("input.deadzoneMouse"),
prop_deadzoneGamepad("input.deadzoneGamepad"),

prop_gamepadFireAxesValue("input.gamepadFireAxesValue"),
prop_gamepadFireIndex("input.gamepadFireIndex"),
prop_gamepadRocketAxesValue("input.gamepadRocketAxesValue"),
prop_gamepadRocketIndex("input.gamepadRocketIndex"),

prop_gamepadMoveLeftAxesValue("input.gamepadMoveLeftAxesValue"),
prop_gamepadMoveLeftIndex("input.gamepadMoveLeftIndex"),
prop_gamepadMoveRightAxesValue("input.gamepadMoveRightAxesValue"),
prop_gamepadMoveRightIndex("input.gamepadMoveRightIndex"),

prop_gamepadMoveForwardAxesValue("input.gamepadMoveForwardAxesValue"),
prop_gamepadMoveForwardIndex("input.gamepadMoveForwardIndex"),
prop_gamepadMoveBackwardAxesValue("input.gamepadMoveBackwardAxesValue"),
prop_gamepadMoveBackwardIndex("input.gamepadMoveBackwardIndex"),

prop_gamepadRotateLeftAxesValue("input.gamepadRotateLeftAxesValue"),
prop_gamepadRotateLeftIndex("input.gamepadRotateLeftIndex"),
prop_gamepadRotateRightAxesValue("input.gamepadRotateRightAxesValue"),
prop_gamepadRotateRightIndex("input.gamepadRotateRightIndex"),

prop_gamepadRotateUpAxesValue("input.gamepadRotateUpAxesValue"),
prop_gamepadRotateUpIndex("input.gamepadRotateUpIndex"),
prop_gamepadRotateDownAxesValue("input.gamepadRotateDownAxesValue"),
prop_gamepadRotateDownIndex("input.gamepadRotateDownIndex"),

prop_gamepadRotateClockwiseAxesValue("input.gamepadRotateClockwiseAxesValue"),
prop_gamepadRotateClockwiseIndex("input.gamepadRotateClockwiseIndex"),
prop_gamepadRotateCClockwiseAxesValue("input.gamepadRotateCClockwiseAxesValue"),
prop_gamepadRotateCClockwiseIndex("input.gamepadRotateCClockwiseIndex"),

prop_gamepadSelectNextAxesValue("input.gamepadSelectNextAxesValue"),
prop_gamepadSelectNextIndex("input.gamepadSelectNextIndex"),
prop_gamepadSelectPreviousAxesValue("input.gamepadSelectPreviousAxesValue"),
prop_gamepadSelectPreviousIndex("input.gamepadSelectPreviousIndex"),
m_targeter(new Targeter(player, camera))
{

    joystickSetupState = -1;
    bumperLeftState = false;
    bumperRightState = false;
    glfwGetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
    m_targeter->setWindowSize(m_windowWidth, m_windowHeight);
    glfwSetCursorPos(m_window, m_windowWidth / 2, m_windowHeight / 2);

    m_cursorMaxDistance = glm::min(m_windowHeight, m_windowWidth) / 2;

    m_mouseControl = false;
    m_lastfocus = glfwGetWindowAttrib(m_window, GLFW_FOCUSED);

    lastIndex = -1;
    lastAxesValue = 0;

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    if (glfwJoystickPresent(GLFW_JOYSTICK_1)){
        gamepadButtonCnt = 0;
        gamepadAxisCnt = 0;
        gamepadButtonValues = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &gamepadButtonCnt);
        gamepadAxisValues = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &gamepadAxisCnt);
    }
}

InputHandler::~InputHandler(){

}


void InputHandler::resizeEvent(const unsigned int width, const unsigned int height){
	m_windowWidth = width;
	m_windowHeight = height;
	m_camera->setViewport(glm::ivec2(m_windowWidth, m_windowHeight));
	m_lastfocus = false;
    m_targeter->setWindowSize(width, height);
}

void InputHandler::keyCallback(int key, int scancode, int action, int mods){
	/* Check here for single-time key-presses, that you do not want fired multiple times, e.g. toggles */
    if (key == GLFW_KEY_F10 && action == GLFW_PRESS &&  glfwJoystickPresent(GLFW_JOYSTICK_1)){
        joystickSetupState = 0;
        glow::debug("Starting Gamepad configuration. Please press the Buttons or Sticks all the way through before hitting Enter.");
        glow::debug("Please press the -fire- button or stick, then hit enter");
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        m_mouseControl = !m_mouseControl;
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS){
        if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            m_targeter->selectNextTarget();
        else
            m_targeter->selectPreviousTarget();
    }
    if (key == GLFW_KEY_B && action == GLFW_PRESS){
        VoxelExplosionGenerator g;
        g.setPosition(m_player->playerShip()->transform().position() + m_player->playerShip()->transform().orientation() * glm::vec3(0, 0, -30));
        g.setOrientation(m_player->playerShip()->transform().orientation());
        g.setScale((float)(rand() % 3) + 1);
        g.setForce((float)(rand() % 2) + 1);
        g.setDensity((rand() % 4) + 2);
        g.spawn();
    }
}

void InputHandler::update(float delta_sec) {
	/* Check here for every-frame events, e.g. view & movement controls */
    if (glfwGetWindowAttrib(m_window, GLFW_FOCUSED)){
        if (m_lastfocus){
            handleKeyboardUpdate();
            if (glfwJoystickPresent(GLFW_JOYSTICK_1))
                setupJoystick(GLFW_JOYSTICK_1);
                handleJoystickUpdate(GLFW_JOYSTICK_1);
            handleMouseUpdate();
        }
    }
	m_lastfocus = glfwGetWindowAttrib(m_window, GLFW_FOCUSED);
}




void InputHandler::handleKeyboardUpdate(){
    if (glfwGetKey(m_window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS){    // move down
        m_player->move(glm::vec3(0, -1, 0));
    }
    if (glfwGetKey(m_window, GLFW_KEY_PAGE_UP) == GLFW_PRESS){      // move up
        m_player->move(glm::vec3(0, 1, 0));
    }
    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS){            // move forward
        m_player->move(glm::vec3(0, 0, -1));
    }
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS){            // move left
        m_player->move(-glm::vec3(1, 0, 0));
    }
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS){            // move backwards
        m_player->move(glm::vec3(0, 0, 1));
    }
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS){            // move right
        m_player->move(glm::vec3(1, 0, 0));
    }
    if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS){            // rotate left
        m_player->rotate(glm::vec3(0, 0, 1));
    }
    if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS){            // rotate right
        m_player->rotate(glm::vec3(0, 0, -1));
    }
    if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){   // boost, not implemented yet
        m_player->boost();
    }
    if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS){            // fire rocket
        m_player->playerShip()->fireAtObject();
    }
}

void InputHandler::handleJoystickUpdate(int joystickEnum){

    gamepadButtonCnt = 0;
    gamepadAxisCnt = 0;
    gamepadButtonValues = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &gamepadButtonCnt);
    gamepadAxisValues = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &gamepadAxisCnt);
    // initialization of Joystick, incase it is removed / replaced

    if (getGamepadInputValue(prop_gamepadSelectPreviousIndex, prop_gamepadSelectPreviousAxesValue) > 0){
        if (!bumperLeftState)
            m_targeter->selectPreviousTarget();
        bumperLeftState = true;
    }
    else {
        bumperLeftState = false;
    }
    if (getGamepadInputValue(prop_gamepadSelectNextIndex, prop_gamepadSelectNextAxesValue) > 0){
        if (!bumperRightState)
            m_targeter->selectNextTarget();
        bumperRightState = true;
    }
    else {
        bumperRightState = false;
    }

    if (getGamepadInputValue(prop_gamepadFireIndex, prop_gamepadFireAxesValue) > 0){
        m_player->playerShip()->fireAtPoint(m_targeter->findTargetPoint(m_windowWidth / 2, m_windowHeight / 2));
    }
    if (getGamepadInputValue(prop_gamepadRocketIndex, prop_gamepadRocketAxesValue) > 0){
        m_player->playerShip()->fireAtObject();
    }
    m_player->move(glm::vec3(-getGamepadInputValue(prop_gamepadMoveLeftIndex, prop_gamepadMoveLeftAxesValue), 0, 0));
    m_player->move(glm::vec3(getGamepadInputValue(prop_gamepadMoveRightIndex, prop_gamepadMoveRightAxesValue), 0, 0));
    m_player->move(glm::vec3(0, 0, -getGamepadInputValue(prop_gamepadMoveForwardIndex, prop_gamepadMoveForwardAxesValue)));
    m_player->move(glm::vec3(0, 0, getGamepadInputValue(prop_gamepadMoveBackwardIndex, prop_gamepadMoveBackwardAxesValue)));
    glm::vec3 rot = glm::vec3(0);
    rot.x =  getGamepadInputValue(prop_gamepadRotateUpIndex, prop_gamepadRotateUpAxesValue)
        - getGamepadInputValue(prop_gamepadRotateDownIndex, prop_gamepadRotateDownAxesValue);
    rot.y = getGamepadInputValue(prop_gamepadRotateLeftIndex, prop_gamepadRotateLeftAxesValue)
        - getGamepadInputValue(prop_gamepadRotateRightIndex, prop_gamepadRotateRightAxesValue);
    rot.z = getGamepadInputValue(prop_gamepadRotateClockwiseIndex, prop_gamepadRotateClockwiseAxesValue)
        - getGamepadInputValue(prop_gamepadRotateCClockwiseIndex, prop_gamepadRotateCClockwiseAxesValue);
    if (glm::length(rot) < prop_deadzoneGamepad){
        rot = glm::vec3(0);
    }
    if (glm::length(rot) > 1){
        rot = glm::normalize(rot);
    }
    m_player->rotate(rot);
}

void InputHandler::handleMouseUpdate(){
    // mouse handling
    double x, y;
    glfwGetCursorPos(m_window, &x, &y);

    // shoot
    if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        m_player->playerShip()->fireAtPoint(m_targeter->findTargetPoint(x, y));
    }

    // spin
    float rel = 20;
    double dis = 0;
    float angX = 0;
    float angY = 0;

    if (m_mouseControl || glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
        glm::vec3 rot;
        x = m_windowWidth / 2 - (int)floor(x);
        y = m_windowHeight / 2 - (int)floor(y);
        x = glm::min((double)m_cursorMaxDistance, x);
        y = glm::min((double)m_cursorMaxDistance, y);
        rot = glm::vec3(y, x, 0);
        rot /= m_cursorMaxDistance;

        if (glm::length(rot) < prop_deadzoneMouse){
            rot = glm::vec3(0);
        }
        if (glm::length(rot) > 1){
            rot = glm::normalize(rot);
        }
        m_player->rotate(rot);

    }
}

void InputHandler::setupJoystick(int joystickEnum){
    if (joystickSetupState < 0)
        return;
    getLastButton(joystickEnum);
    //glow::debug("state: %; axesValue: %; index: %;", joystickSetupState, lastAxesValue, lastIndex);
    if (lastIndex == -1)
        return;
    if (glfwGetKey(m_window, GLFW_KEY_ENTER) == GLFW_PRESS){
        switch (joystickSetupState){
        case 0: prop_gamepadFireAxesValue.set(lastAxesValue);
            prop_gamepadFireIndex.set(lastIndex);
            glow::debug("-fire bullet- button set.");
            glow::debug("Please press the -fire rocket- button or stick, then hit enter");
            break;
        case 1: prop_gamepadRocketAxesValue.set(lastAxesValue);
            prop_gamepadRocketIndex.set(lastIndex);
            glow::debug("-fire rocket- button set.");
            glow::debug("Please press the -move left- button or stick, then hit enter");
            break;
        case 2: prop_gamepadMoveLeftAxesValue.set(lastAxesValue);
            prop_gamepadMoveLeftIndex.set(lastIndex);
            glow::debug("-move left- button set.");
            glow::debug("Please press the -move right- button or stick, then hit enter");
            break;
        case 3: prop_gamepadMoveRightAxesValue.set(lastAxesValue);
            prop_gamepadMoveRightIndex.set(lastIndex);
            glow::debug("-move right- button set.");
            glow::debug("Please press the -move forward- button or stick, then hit enter");
            break;
        case 4: prop_gamepadMoveForwardAxesValue.set(lastAxesValue);
            prop_gamepadMoveForwardIndex.set(lastIndex);
            glow::debug("-move forward- button set.");
            glow::debug("Please press the -move backward- button or stick, then hit enter");
            break;
        case 5: prop_gamepadMoveBackwardAxesValue.set(lastAxesValue);
            prop_gamepadMoveBackwardIndex.set(lastIndex);
            glow::debug("-move backward- button set.");
            glow::debug("Please press the -rotate left- button or stick, then hit enter");
            break;
        case 6: prop_gamepadRotateLeftAxesValue.set(lastAxesValue);
            prop_gamepadRotateLeftIndex.set(lastIndex);
            glow::debug("-rotate left- button set.");
            glow::debug("Please press the -rotate right- button or stick, then hit enter");
            break;
        case 7: prop_gamepadRotateRightAxesValue.set(lastAxesValue);
            prop_gamepadRotateRightIndex.set(lastIndex);
            glow::debug("-rotate right- button set.");
            glow::debug("Please press the -rotate up- button or stick, then hit enter");
            break;
        case 8: prop_gamepadRotateUpAxesValue.set(lastAxesValue);
            prop_gamepadRotateUpIndex.set(lastIndex);
            glow::debug("-rotate up- button set.");
            glow::debug("Please press the -rotate down- button or stick, then hit enter");
            break;
        case 9: prop_gamepadRotateDownAxesValue.set(lastAxesValue);
            prop_gamepadRotateDownIndex.set(lastIndex);
            glow::debug("-rotate down- button set.");
            glow::debug("Please press the -rotate clockwise- button or stick, then hit enter");
            break;
        case 10: prop_gamepadRotateClockwiseAxesValue.set(lastAxesValue);
            prop_gamepadRotateClockwiseIndex.set(lastIndex);
            glow::debug("-rotate clockwise- button set.");
            glow::debug("Please press the -rotate counterclockwise- button or stick, then hit enter");
            break;
        case 11: prop_gamepadRotateCClockwiseAxesValue.set(lastAxesValue);
            prop_gamepadRotateCClockwiseIndex.set(lastIndex);
            glow::debug("-rotate counterclockwise- button set.");
            glow::debug("Please press the -select next target- button or stick, then hit enter");
            break;
        case 12: prop_gamepadSelectNextAxesValue.set(lastAxesValue);
            prop_gamepadSelectNextIndex.set(lastIndex);
            glow::debug("-select next target- button set.");
            glow::debug("Please press the -select previous target- button or stick, then hit enter");
            break;
        case 13: prop_gamepadSelectPreviousAxesValue.set(lastAxesValue);
            prop_gamepadSelectPreviousIndex.set(lastIndex);
            glow::debug("-select previous- button set.");
            break;
        }
        joystickSetupState++;
        if (joystickSetupState == 14){
            glow::debug("Gamepad configuration complete");
            joystickSetupState = -1;
        }
        lastAxesValue = 0;
        lastIndex = -1;
    }
}

void InputHandler::getLastButton(int joystickEnum){
    int cntButtons = 0;
    int cntAxes = 0;
    const unsigned char *buttons = glfwGetJoystickButtons(joystickEnum, &cntButtons);
    const float *axes = glfwGetJoystickAxes(joystickEnum, &cntAxes);
    for (int i = 0; i < cntButtons; i++){ // get pushed button
        if (buttons[i] == GLFW_PRESS){
            lastIndex = i;
            lastAxesValue = 0;
            return;
        }
    }
    for (int i = 0; i < cntAxes; i++){ // get pushed axes
        if (glm::abs(axes[i]) > prop_deadzoneGamepad){
            // greater maxValue for same axes
            if (lastIndex == i){ 
                if (glm::abs(lastAxesValue) < glm::abs(axes[i]))
                    lastAxesValue = axes[i];
                return;
            }
            // new axes
            lastIndex = i;
            lastAxesValue = axes[i];
            return;
        }
    }
}

float InputHandler::getGamepadInputValue(int index, float axisValue) {
    if (index == -1)
        return 0;
    float inputValue = 0;
    if (axisValue == 0) {
        if (gamepadButtonValues[index] == GLFW_PRESS)
            return 1;
        else
            return 0;
    } else {
        if (glm::abs(gamepadAxisValues[index]) > prop_deadzoneGamepad) {
            float relativeValue = gamepadAxisValues[index] / axisValue;
            if (relativeValue > 0) {
                return glm::min(relativeValue, 1.0f);
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }
}
