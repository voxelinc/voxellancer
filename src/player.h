#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "equipment/enginestate.h"

#include "worldobject/handle/handle.h"


class Aimer;
class Camera;
class CameraDolly;
class CameraHead;
class HUD;
class GamePlay;

class Player {
public:
    Player(GamePlay* gamePlay);
    ~Player();

    Ship* ship();
    void setShip(Ship *ship);

    void update(float deltaSec);

    CameraDolly& cameraDolly();
    CameraHead& cameraHead();
    const CameraHead& cameraHead() const;

    HUD& hud();

    void fire();

    void move(const glm::vec3& vec);
    void rotate(const glm::vec3& euler);


protected:
    GamePlay* m_gamePlay;
    Handle<Ship> m_ship;
    std::unique_ptr<CameraDolly> m_cameraDolly;
    std::unique_ptr<HUD> m_hud;
    std::unique_ptr<Aimer> m_aimer;
    EngineState m_engineState;
};

