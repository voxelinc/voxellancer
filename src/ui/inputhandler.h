#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "input/inputmapping.h"
#include "property/propertymanager.h"
#include "property/property.h"
#include "worldobject/ship.h"
#include "ui/targeter.h"

class WorldObject;

struct actionKeyMapping {
    Property<InputMapping> primaryMapping;
    Property<InputMapping> secondaryMapping;
    bool toggleAction;
    bool toggleStatus;
    std::string name;

    actionKeyMapping(char* primary, char* secondary, std::string name) :
        primaryMapping(primary),
        secondaryMapping(secondary),
        toggleAction(false),
        toggleStatus(false),
        name(name)
    {};

    actionKeyMapping(char* primary, char* secondary, std::string name, bool toggleAction) :
        primaryMapping(primary),
        secondaryMapping(secondary),
        toggleAction(toggleAction),
        toggleStatus(false),
        name(name)
    {};
};

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
    void handleUpdate();
    //void handleKeyboardUpdate();
    //void handleJoystickUpdate(int joystickEnum);
    void handleMouseUpdate();

    void handleFireActions();
    void handleMoveActions();
    void handleRotateActions();
    void handleTargetSelectActions();

    void setupJoystick();
    void getLastButton();
    float getInputValue(actionKeyMapping* action);
    float getInputValue(InputMapping mapping);
    bool setActionInputMapping(actionKeyMapping* action, bool primary);
    bool getLastPrimaryInput();
    bool getLastSecondaryInput();

    void setupJoystickControls();
    int joystickSetupState;

    int gamepadButtonCnt, gamepadAxisCnt;
    const unsigned char *gamepadButtonValues;
    const float *gamepadAxisValues;

    bool m_mouseControl;
    int m_windowWidth, m_windowHeight;
    int m_cursorMaxDistance;
    int m_lastfocus;
    InputMapping lastPrimaryInput;
    InputMapping lastSecondaryInput;
    bool setupPrimaryInputInProgress;
    bool setupSecondaryInputInProgress;


    Property<float> prop_deadzoneMouse;
    Property<float> prop_deadzoneGamepad;

    actionKeyMapping fireAction;
    actionKeyMapping rocketAction;

    actionKeyMapping moveLeftAction;
    actionKeyMapping moveRightAction;
    actionKeyMapping moveForwardAction;
    actionKeyMapping moveBackwardAction;

    actionKeyMapping rotateLeftAction;
    actionKeyMapping rotateRightAction;
    actionKeyMapping rotateUpAction;
    actionKeyMapping rotateDownAction;
    actionKeyMapping rotateClockwiseAction;
    actionKeyMapping rotateCClockwiseAction;

    actionKeyMapping selectNextAction;
    actionKeyMapping selectPreviousAction;

};
