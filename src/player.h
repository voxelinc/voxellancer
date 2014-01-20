#pragma once

#include "worldobject/ship.h"

#include "camera.h"

class Player
{

public:
    Player(Camera *camera);

    void setShip(Ship *ship);
    void move(glm::vec3 direction);
    void rotate(glm::vec3 direction);
    void applyUpdate();
    void setFollowCam();
    Ship* ship();
    void setShipToCam(float deltaSec);
    void boost();


private:
    Camera *m_camera;
    Ship *m_ship;
    glm::vec3 m_shipOffset;
    glm::vec3 m_acceleration;
    glm::vec3 m_accelerationAngular;

};
