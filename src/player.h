#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "worldobject/handle/handle.h"

class Camera;
class CameraDolly;
class HUD;

class Player {
public:
    Player();

    void setShip(Ship *ship);

    void move(const glm::vec3& direction);
    void rotate(const glm::vec3& direction);

    void update(float deltaSec);

    Ship* playerShip();
    CameraDolly& cameraDolly();
    HUD& hud();

    glm::vec3 cameraPosition();
    glm::quat cameraOrientation();

protected:
    Handle<Ship> m_playerShip;
    std::shared_ptr<CameraDolly> m_cameraDolly;
    std::shared_ptr<HUD> m_hud;

    glm::vec3 m_acceleration;
    glm::vec3 m_accelerationAngular;
};

