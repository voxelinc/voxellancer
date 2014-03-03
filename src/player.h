#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "ai/character.h"

#include "equipment/enginestate.h"

#include "worldobject/handle/handle.h"


class Aimer;
class Camera;
class CameraDolly;
class CameraHead;
class EnemySelector;
class HUD;
class GamePlay;

class Player : public Character {
public:
    Player(GamePlay* gamePlay);
    ~Player();

    Ship* ship();
    void setShip(Ship *ship);

    void selectNextEnemy();

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
    std::unique_ptr<EnemySelector> m_enemySelector;
    EngineState m_engineState;
};

