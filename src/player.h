#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "camera/cameradolly.h"

#include "worldobject/handle/handle.h"

#include "ui/hud/hud.h"


class TargetSelector;

class Camera;
class CameraDolly;

class Game;

class Player {
public:
    Player(Game* game);

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

    void selectTarget(bool next);
    void setTarget(WorldObject* target);


protected:
    Game* m_game;
    Handle<Ship> m_playerShip;
    CameraDolly m_cameraDolly;
    HUD m_hud;
    TargetSelector* m_targetSelector;

    glm::vec3 m_acceleration;
    glm::vec3 m_accelerationAngular;

    template<typename IteratorType>
    WorldObject* findNextTarget(IteratorType begin, IteratorType end);

    std::function<bool(WorldObject*)> canLockOnPredicate();

};

