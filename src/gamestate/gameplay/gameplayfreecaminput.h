#pragma once

#include <vector>

#include "input/inputmapping.h"

#include "ui/actionkeymapping.h"
#include "utils/statemachine/trigger.h"

#include "property/property.h"


class WorldObject;
class GameState;
class HUD;
class HMD;
class CameraDolly;

class GamePlayFreecamInput {
public:
    GamePlayFreecamInput(CameraDolly* cameraDolly);

    //void resizeEvent(const unsigned int width, const unsigned int height);
    //void keyCallback(int key, int scancode, int action, int mods);
    //void mouseButtonCallback(int button, int action, int mods);
	void update(float deltaSec);

    const glm::vec3& position();
    const glm::quat& orientation();
    void setPosition(const glm::vec3& position);
    void setOrientation(const glm::quat& orientation);


protected:
    CameraDolly* m_cameraDolly;
    SecondaryInputValues m_secondaryInputValues;
    std::vector<ActionKeyMapping*> m_actions;

    int m_lastfocus;

    void processUpdate();
    void processMouseUpdate(float deltaSec);
    void processHMDUpdate();
    void applyUpdates();

    void processMoveActions();
    void processRotateActions();

    float getInputValue(ActionKeyMapping* action);
    float getInputValue(InputMapping mapping);

    void addActionsToVector();
    void retrieveInputValues();

    float m_currentTimePressed;

    Property<float> prop_deadzoneMouse;
    Property<float> prop_deadzoneGamepad;

    Property<float> prop_maxClickTime;

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

    glm::vec3 m_moveUpdate;
    glm::vec3 m_rotateUpdate;
    float m_moveFactor;
    float m_rotateFactor;
    glm::vec3 m_position;
    glm::quat m_orientation;
};
