#pragma once

#include <list>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "worldobject/worldobjecthandle.h"


class Ship;
class WorldObject;

class BoardComputer
{
public:
    BoardComputer(Ship& ship);
    
    void moveTo(const glm::vec3& position, float minDistance = 0);
    void rotateTo(const glm::vec3& position);
    void shootBullet(const std::list<std::shared_ptr<WorldObjectHandle>>& targets);
    void shootRockets(std::shared_ptr<WorldObjectHandle> target);

protected:
    Ship& m_ship;
};

