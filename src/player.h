#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "worldobject/handle/handle.h"
#include "worldobject/components/enginestate.h"


class Camera;
class CameraDolly;
class CameraHead;
class HUD;
class GamePlay;

class Player {
public:
    Player(GamePlay* inGame);
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
    GamePlay* m_inGame;
    Handle<Ship> m_ship;
    std::unique_ptr<CameraDolly> m_cameraDolly;
    std::unique_ptr<HUD> m_hud;
    EngineState m_engineState;
};

