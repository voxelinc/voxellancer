#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "camera/cameradolly.h"

#include "ui/hud.h"

#include "worldobject/components/enginestate.h"
#include "worldobject/handle/handle.h"


class Camera;
class CameraDolly;
class HUD;

class Player {
public:
    Player();

    Ship* ship();
    void setShip(Ship *ship);

    void update(float deltaSec);

    CameraDolly& cameraDolly();
    HUD& hud();

    void move(const glm::vec3& vec);
    void rotate(const glm::vec3& euler);


protected:
    Handle<Ship> m_ship;
    CameraDolly m_cameraDolly;
    HUD m_hud;
    EngineState m_engineState;
};

