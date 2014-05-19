#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "equipment/enginestate.h"

#include "utils/handle/handle.h"


class Aimer;
class Camera;
class CameraHead;
class CameraDolly;
class HUD;
class Mission;
class MissionSystem;
class Sector;
class TargetSelector;
class Universe;

class Player {
public:
    Player(Universe& universe);
    virtual ~Player();

    Ship* ship();
    void setShip(Ship *ship);

    Sector* sector();
    Universe& universe();

    void update(float deltaSec);

    CameraHead& cameraHead();

    HUD& hud();

    void fire();

    void move(const glm::vec3& vec);
    void rotate(const glm::vec3& euler);

    void selectTarget(bool next);
    void setTarget(WorldObject* target);


protected:
    Universe& m_universe;
    Handle<Ship> m_ship;
    Sector* m_sector;
    std::unique_ptr<CameraDolly> m_cameraDolly;
    std::unique_ptr<HUD> m_hud;
    std::unique_ptr<TargetSelector> m_targetSelector;
    std::unique_ptr<Aimer> m_aimer;
    EngineState m_engineState;
};

