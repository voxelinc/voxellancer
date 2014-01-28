#pragma once

#include "camera/camera.h"
#include "camera/cameradolly.h"

#include "ui/hud/hud.h"

#include "worldobject/ship.h"


class Game;

class Player {
public:
    Player(Game* game);

    void setShip(Ship *ship);

    void move(glm::vec3 direction);
    void rotate(glm::vec3 direction);

    void fire();

    void update(float deltaSec);

    Ship* playerShip();
    CameraDolly& cameraDolly();
    HUD& hud();


protected:
    Game* m_game;
    Ship* m_playerShip;
    CameraDolly m_cameraDolly;
    HUD m_hud;

    glm::vec3 m_acceleration;
    glm::vec3 m_accelerationAngular;
};

