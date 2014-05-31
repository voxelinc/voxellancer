#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "equipment/enginestate.h"

#include "utils/handle/handle.h"

#include "ai/character.h"


class Aimer;
class Camera;
class CameraHead;
class CameraDolly;
class HUD;
class Mission;
class MissionSystem;
class TargetSelector;
class PlayerBoardComputer;

class Player {
public:
    Player();
    ~Player();

    Ship* ship();
    void setShip(Ship *ship);
    bool hasShip();

    void update(float deltaSec);

    CameraHead& cameraHead();

    HUD& hud();

    void selectTarget(bool next);
    void setTarget(WorldObject* target);

    void joinSelectedSquad();
    void leaveSquad();

    Character& character();
    PlayerBoardComputer& playerBoardComputer();

protected:
    std::unique_ptr<CameraDolly> m_cameraDolly;
    std::unique_ptr<HUD> m_hud;
    std::unique_ptr<TargetSelector> m_targetSelector;

    Handle<Ship> m_ship;
    PlayerBoardComputer* m_boardComputer;
    
    Handle<Character> m_character;
};

