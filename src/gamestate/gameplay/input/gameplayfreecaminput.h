#pragma once

#include <vector>

#include "input/inputmapping.h"
#include "gamestate/gameplay/gameplayinput.h"

#include "ui/actionkeymapping.h"
#include "utils/statemachine/trigger.h"

#include "property/property.h"

#include "camera/cameradolly.h"


class WorldObject;
class GameState;
class HUD;
class HMD;
class CameraDolly;

class GamePlayFreecamInput : public GamePlayInput {
public:
    GamePlayFreecamInput();

    void resizeEvent(const unsigned int width, const unsigned int height) override;
    //void keyCallback(int key, int scancode, int action, int mods);
    //void mouseButtonCallback(int button, int action, int mods);
	virtual void update(float deltaSec) override;

    const glm::vec3& position();
    const glm::quat& orientation();
    void setPosition(const glm::vec3& position);
    void setOrientation(const glm::quat& orientation);

    CameraHead& cameraHead();


protected:
    std::unique_ptr<CameraDolly> m_cameraDolly;

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

    Property<float> prop_deadzoneMouse;
    Property<float> prop_deadzoneGamepad;

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
    Property<float> prop_moveFactor;
    Property<float> prop_rotateFactor;
    glm::vec3 m_position;
    glm::quat m_orientation;
};
