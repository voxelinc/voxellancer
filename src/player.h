#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "equipment/enginestate.h"

#include "worldobject/handle/handle.h"


class Camera;
class CameraDolly;
class CameraHead;
class HUD;

class Game;

class Player {
public:
    Player(Game* game);
    ~Player();

    Ship* ship();
    void setShip(Ship *ship);

    void update(float deltaSec);

    CameraDolly& cameraDolly();
    CameraHead& cameraHead();
    HUD& hud();

    void fire();

    void move(const glm::vec3& vec);
    void rotate(const glm::vec3& euler);



protected:
    Game* m_game;
    Handle<Ship> m_ship;
    std::unique_ptr<CameraDolly> m_cameraDolly;
    std::unique_ptr<HUD> m_hud;
    EngineState m_engineState;
};

