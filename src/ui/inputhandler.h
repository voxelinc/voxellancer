#pragma once

#include <vector>

#include "property/property.h"
#include "inputconfigurator.h"
#include "actionkeymapping.h"


class Player;
class WorldObject;
class InputConfigurator;
class HUD;
class HMD;
class TargetSelector;
class Player;

class InputHandler {
public:
    InputHandler(Player& player);

    void setHMD(HMD& hmd);

    void resizeEvent(const unsigned int width, const unsigned int height);
    void keyCallback(int key, int scancode, int action, int mods);
    void mouseButtonCallback(int button, int action, int mods);
	void update(float deltaSec);


protected:
    Player* m_player;
    HMD* m_hmd;
    InputConfigurator* m_inputConfigurator;
    SecondaryInputValues m_secondaryInputValues;
    std::vector<ActionKeyMapping*> m_actions;

    bool m_mouseControl;
    int m_cursorMaxDistance;
    int m_lastfocus;

    void toggleControls();

    void processUpdate();
    void processMouseUpdate(float deltaSec);
    void processHMDUpdate();

    void processFireActions();
    void processMoveActions();
    void processRotateActions();
    void processTargetSelectActions();

    float getInputValue(ActionKeyMapping* action);
    float getInputValue(InputMapping mapping);

    void addActionsToVector();
    void setupJoystickControls();
    void retrieveInputValues();

    float m_currentTimePressed;

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

    void placeCrossHair(double winX, double winY);
};
