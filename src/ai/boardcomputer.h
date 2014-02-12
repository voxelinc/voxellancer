#pragma once

#include <vector>
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
    
    void moveTo(const glm::vec3& position, bool decelerate = true);
    void rotateTo(const glm::vec3& position, const glm::vec3& up = glm::vec3(0, 0, 0));
    void shootBullet(const std::vector<Handle<WorldObject>>& targets);
    void shootRockets(Handle<WorldObject> target);

protected:
    void rotateUpTo(const glm::vec3& up);
    void rotateUpAuto(const glm::quat& rotation);

    Ship& m_ship;

};

