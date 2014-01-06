#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "property/propertymanager.h"
#include "property/property.h"
#include "worldobject/ship.h"
#include "ui/targeter.h"

class WorldObject;

class InputHandler {
public:
    InputHandler(GLFWwindow *window, Camera *camera);
    InputHandler(GLFWwindow *window, Player *player, Camera *camera);
	virtual ~InputHandler();

	void resizeEvent(const unsigned int width, const unsigned int height);
	void keyCallback(int key, int scancode, int action, int mods);
	void update(float delta_sec);

protected:
    GLFWwindow *m_window;
    Camera* m_camera;
    Player* m_player;
    Targeter* m_targeter;

    void toggleControls();
    void handleKeyboardUpdate();
    void handleJoystickUpdate(int joystickEnum);
    void handleMouseUpdate();
    void setupJoystick(int joystickEnum);
    void getLastButton(int joystickEnum);
    float getGamepadInputValue(int index, float axisValue);

    int joystickSetupState;
    int gamepadButtonCnt, gamepadAxisCnt;
    const unsigned char *gamepadButtonValues;
    const float *gamepadAxisValues;
    bool bumperLeftState, bumperRightState;
    bool m_mouseControl;
    int m_windowWidth, m_windowHeight;
    int m_cursorMaxDistance;
	int m_lastfocus;
    float lastAxesValue;
    int lastIndex;

    Property<float> prop_deadzoneMouse;
    Property<float> prop_deadzoneGamepad;

    Property<float> prop_gamepadFireAxesValue;
    Property<int> prop_gamepadFireIndex;
    Property<float> prop_gamepadRocketAxesValue;
    Property<int> prop_gamepadRocketIndex;

    Property<float> prop_gamepadMoveLeftAxesValue;
    Property<int> prop_gamepadMoveLeftIndex;
    Property<float> prop_gamepadMoveRightAxesValue;
    Property<int> prop_gamepadMoveRightIndex;

    Property<float> prop_gamepadMoveForwardAxesValue;
    Property<int> prop_gamepadMoveForwardIndex;
    Property<float> prop_gamepadMoveBackwardAxesValue;
    Property<int> prop_gamepadMoveBackwardIndex;

    Property<float> prop_gamepadRotateRightAxesValue;
    Property<int> prop_gamepadRotateRightIndex;
    Property<float> prop_gamepadRotateLeftAxesValue;
    Property<int> prop_gamepadRotateLeftIndex;

    Property<float> prop_gamepadRotateUpAxesValue;
    Property<int> prop_gamepadRotateUpIndex;
    Property<float> prop_gamepadRotateDownAxesValue;
    Property<int> prop_gamepadRotateDownIndex;

    Property<float> prop_gamepadRotateClockwiseAxesValue;
    Property<int> prop_gamepadRotateClockwiseIndex;
    Property<float> prop_gamepadRotateCClockwiseAxesValue;
    Property<int> prop_gamepadRotateCClockwiseIndex;

    Property<float> prop_gamepadSelectNextAxesValue;
    Property<int> prop_gamepadSelectNextIndex;
    Property<float> prop_gamepadSelectPreviousAxesValue;
    Property<int> prop_gamepadSelectPreviousIndex;

};
