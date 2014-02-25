#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "equipment/enginestate.h"

#include "worldobject/handle/handle.h"

class TargetSelector;

class Aimer;
class Camera;
class CameraHead;
class HUD;
class CameraDolly;

class Game;

class Player {
public:
    Player(Game* game);
    ~Player();

    Ship* ship();
    void setShip(Ship *ship);

    void update(float deltaSec);

    CameraHead& cameraHead();
    CameraDolly& cameraDolly();
    HUD& hud();

    void fire();

    void move(const glm::vec3& vec);
    void rotate(const glm::vec3& euler);


    void selectTarget(bool next);
    void setTarget(WorldObject* target);


protected:
    Game* m_game;
    Handle<Ship> m_ship;
    std::unique_ptr<CameraDolly> m_cameraDolly;
    std::unique_ptr<HUD> m_hud;
    std::unique_ptr<TargetSelector> m_targetSelector;
    std::unique_ptr<Aimer> m_aimer;
    EngineState m_engineState;
};

