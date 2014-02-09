#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "camera/cameradolly.h"

#include "ui/hud/hud.h"

#include "worldobject/handle/handle.h"


class Camera;
class CameraDolly;
class HUD;
class InGame;

class Player {
public:
    Player(InGame* inGame);

    void setShip(Ship *ship);

    void move(const glm::vec3& direction);
    void rotate(const glm::vec3& direction);

    void fire();

    void update(float deltaSec);

    Ship* playerShip();
    CameraDolly& cameraDolly();
    HUD& hud();

    glm::vec3 cameraPosition();
    glm::quat cameraOrientation();


protected:
    InGame* m_inGame;
    Handle<Ship> m_playerShip;
    CameraDolly m_cameraDolly;
    HUD m_hud;

    glm::vec3 m_acceleration;
    glm::vec3 m_accelerationAngular;
};

