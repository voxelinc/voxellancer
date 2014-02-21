#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "worldobject/handle/handle.h"


class Camera;
class CameraDolly;
class CameraHead;
class HUD;
class GamePlay;

class Player {
public:
    Player(GamePlay* inGame);

    Ship* ship();
    void setShip(Ship *ship);

    void update(float deltaSec);


    CameraDolly& cameraDolly();
    CameraHead& cameraHead();
    HUD& hud();



protected:
    GamePlay* m_inGame;
    Handle<Ship> m_ship;
    std::unique_ptr<CameraDolly> m_cameraDolly;
    std::unique_ptr<HUD> m_hud;
};

