#pragma once

#include "camera/camera.h"
#include "camera/cameradolly.h"

#include "ui/hud/hud.h"

#include "worldobject/ship.h"


class Player {
public:
    Player();

    void setShip(Ship *ship);

    void move(glm::vec3 direction);
    void rotate(glm::vec3 direction);

    void update(float deltaSec);

    Ship* playerShip();
    CameraDolly& cameraDolly();
    HUD& hud();


protected:
    Ship* m_playerShip;
    CameraDolly m_cameraDolly;
    HUD m_hud;

    glm::vec3 m_acceleration;
    glm::vec3 m_accelerationAngular;
};

