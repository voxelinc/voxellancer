#pragma once

#include <list>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "worldobject/handle/handle.h"


class Ship;
class WorldObject;

class BoardComputer
{
public:
    BoardComputer(Ship& ship);

    void moveTo(const glm::vec3& position);
    void rotateTo(const glm::vec3& position, const glm::vec3& up = glm::vec3(0, 0, 0));
    void shootBullet(const std::list<Handle<WorldObject>>& targets);
    void shootRockets(Handle<WorldObject> target);

protected:
    Ship& m_ship;

    void rotateUpTo(const glm::vec3& up);
    void rotateUpAuto(const glm::quat& rotation);

    void setDirectionalAcceleration(const glm::vec3& directional);
    void setAngularAcceleration(const glm::vec3& angular);
};


