#pragma once

#include <vector>

#include "etc/hmd/hmd.h"

#include "gamestate/gamestate.h"

#include "ui/inputconfigurator.h"

#include "utils/fsm/trigger.h"

#include "property/property.h"

#include "ui/targetselector.h"


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
        name(name)
    {
    }

    ActionKeyMapping(char* primary, char* secondary, std::string name, bool toggleAction) :
        primaryMapping(primary),
        secondaryMapping(secondary),
        toggleAction(toggleAction),
        toggleStatus(false),
        name(name)
    {
    }
};

struct SecondaryInputValues {
    int buttonCnt, axisCnt;
    const unsigned char *buttonValues;
    const float *axisValues;

    SecondaryInputValues();
};

class GamePlayMainInput {
public:
    GamePlayMainInput(Player *player);

    void setPauseTrigger(const Trigger<GameState>& pauseTrigger);

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

    void processUpdate();
    void processMouseUpdate();
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

    Trigger<GameState> m_pauseTrigger;

    void placeCrossHair(double winX, double winY);
};
