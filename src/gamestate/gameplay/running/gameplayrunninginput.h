#pragma once

#include <vector>

#include "input/inputmapping.h"

#include "ui/actionkeymapping.h"
#include "utils/statemachine/trigger.h"

#include "property/property.h"


class Player;
class WorldObject;
class InputConfigurator;
class GameState;
class HUD;
class HMD;
class Player;

class GamePlayRunningInput {
public:
    GamePlayRunningInput();

    void resizeEvent(const unsigned int width, const unsigned int height);
    void keyCallback(int key, int scancode, int action, int mods);
    void mouseButtonCallback(int button, int action, int mods);
	void update(float deltaSec);


protected:
    InputConfigurator* m_inputConfigurator;
    SecondaryInputValues m_secondaryInputValues;
    std::vector<ActionKeyMapping*> m_actions;
    bool m_centerCrosshair;
    glm::vec2 m_lastMousePos;

    bool m_mouseControl;
    int m_cursorMaxDistance;
    int m_lastfocus;

    void toggleControls();

    void processUpdate();
    void processMouseUpdate(float deltaSec);
    void processHMDUpdate();
    void applyUpdates();

    void processFireActions();
    void processMoveActions();
    void processRotateActions();
    void processTargetSelectActions();

    float getInputValue(ActionKeyMapping* action);
    float getInputValue(InputMapping mapping);

    void addActionsToVector();
    void setupJoystickControls();
    void retrieveInputValues();

    float m_currentTimePressedLeft;
    float m_currentTimePressedRight;

    Property<float> prop_deadzoneMouse;
    Property<float> prop_deadzoneGamepad;

    Property<float> prop_maxClickTime;

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

    glm::vec3 m_moveUpdate;
    glm::vec3 m_rotateUpdate;
    bool m_fireUpdate;
    bool m_rocketUpdate;

    void placeCrossHair(double winX, double winY);
};
