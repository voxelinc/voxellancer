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
    
    void moveTo(glm::vec3 position, float minDistance = 10.0f);
    void rotateTo(glm::vec3 orientation);
    void shootBullet(const std::list<std::shared_ptr<WorldObjectHandle>>& targets);
    void shootRockets(std::shared_ptr<WorldObjectHandle> target);

protected:
    Ship& m_ship;
};

