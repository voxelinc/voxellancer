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
    
    void moveTo(glm::vec3 position);
    void rotateTo(glm::quat orientation);
    void shootBullet(const std::list<Handle<WorldObject>>& targets);
    void shootRockets(Handle<WorldObject> target);

protected:
    Ship& m_ship;
};

