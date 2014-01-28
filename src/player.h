#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "worldobject/handle/handle.h"

#include "camera/cameradolly.h"
#include "ui/hud.h"

class Camera;
class CameraDolly;
class HUD;

class Player {
public:
    Player();
    ~Player();

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
    CameraDolly m_cameraDolly;
    HUD m_hud;

    glm::vec3 m_acceleration;
    glm::vec3 m_accelerationAngular;
};

