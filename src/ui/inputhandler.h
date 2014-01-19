#pragma once

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "camera/cameradolly.h"

#include "etc/hmd/hmdinputhandler.h"

#include "property/propertymanager.h"
#include "property/property.h"

#include "ui/crosshair.h"

#include "worldobject/ship.h"

#include "inputconfigurator.h"
#include "targetselector.h"


class WorldObject;
class InputConfigurator;
class HUD;

struct ActionKeyMapping {
    Property<InputMapping> primaryMapping;
    Property<InputMapping> secondaryMapping;
    bool toggleAction;
    bool toggleStatus;
    std::string name;

    ActionKeyMapping(char* primary, char* secondary, std::string name) :
        primaryMapping(primary),
        secondaryMapping(secondary),
        toggleAction(false),
        toggleStatus(false),
        name(name) {
};

    ActionKeyMapping(char* primary, char* secondary, std::string name, bool toggleAction) :
        primaryMapping(primary),
        secondaryMapping(secondary),
        toggleAction(toggleAction),
        toggleStatus(false),
        name(name)
    {};
};

struct SecondaryInputValues {
    int buttonCnt, axisCnt;
    const unsigned char *buttonValues;
    const float *axisValues;

    SecondaryInputValues(){
        buttonCnt = 0;
        axisCnt = 0;
        buttonValues = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCnt);
        axisValues = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axisCnt);
    }
};

class InputHandler {
public:
    InputHandler(Player *player);

    void setHMD(HMD* hmd);

	void resizeEvent(const unsigned int width, const unsigned int height);
	void keyCallback(int key, int scancode, int action, int mods);
	void update(float deltaSec);


protected:
    Player* m_player;
    HMD* m_hmd;
    TargetSelector* m_targetSelector;
    InputConfigurator* m_inputConfigurator;
    SecondaryInputValues m_secondaryInputValues;
    std::vector<ActionKeyMapping*> m_actions;

    bool m_mouseControl;
    int m_cursorMaxDistance;
    int m_lastfocus;


protected:
    void toggleControls();

    void handleUpdate();
    void handleMouseUpdate();

    void handleFireActions();
    void handleMoveActions();
    void handleRotateActions();
    void handleTargetSelectActions();

    float getInputValue(ActionKeyMapping* action);
    float getInputValue(InputMapping mapping);

    void addActionsToVector();

    void setupJoystickControls();

    void retrieveInputValues();


    Property<float> prop_deadzoneMouse;
    Property<float> prop_deadzoneGamepad;

    ActionKeyMapping fireAction;
    ActionKeyMapping rocketAction;

    ActionKeyMapping moveLeftAction;
    ActionKeyMapping moveRightAction;
    ActionKeyMapping moveForwardAction;
    ActionKeyMapping moveBackwardAction;

    ActionKeyMapping rotateLeftAction;
    ActionKeyMapping rotateRightAction;
    ActionKeyMapping rotateUpAction;
    ActionKeyMapping rotateDownAction;
    ActionKeyMapping rotateClockwiseAction;
    ActionKeyMapping rotateCClockwiseAction;

    ActionKeyMapping selectNextAction;
    ActionKeyMapping selectPreviousAction;

    glm::vec3 findTargetPoint();
    void placeCrossHair(double winX, double winY);
};
