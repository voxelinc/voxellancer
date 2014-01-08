#pragma once

#include <list>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Ship;
class WorldObject;

class BoardComputer
{
public:
    BoardComputer(Ship& ship);
    
    void moveTo(glm::vec3 position);
    void rotateTo(glm::quat orientation);
    void shootBullet(const std::list<std::shared_ptr<WorldObjectHandle>>& targets);
    void ShootRockets(std::shared_ptr<WorldObjectHandle> target);

protected:
    Ship& m_ship;
};

