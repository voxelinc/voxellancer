#pragma once

#include "camera/camera.h"
#include "camera/cameradolly.h"

#include "ui/hud.h"

#include "worldobject/ship.h"



class Player
{

public:
    Player();

    void setShip(Ship *ship);

    void move(glm::vec3 direction);
    void rotate(glm::vec3 direction);

    void applyAcceleration();

    void update(float deltaSec);
    void draw();

    Ship* playerShip();
    CameraDolly& cameraDolly();
    HUD& hud();


private:
    Ship* m_playerShip;
    glm::vec3 acc;
    glm::vec3 accAng;

    CameraDolly m_cameraDolly;
    HUD m_hud;
};

