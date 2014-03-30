#pragma once

#include <vector>
#include <list>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "equipment/enginestate.h"

#include "utils/handle/handle.h"


class WorldObject;

class BoardComputer {
public:
    BoardComputer(WorldObject* worldObject);

    WorldObject* worldObject();

    const EngineState& engineState() const;

    void moveTo(const glm::vec3& position, bool decelerate = true);
    void rotateTo(const glm::vec3& position, const glm::vec3& up = glm::vec3(0, 0, 0));

    void shootBullet(const std::vector<Handle<WorldObject>>& targets);
    void shootRockets(Handle<WorldObject>& target);

    void update(float deltaSec);


protected:
    WorldObject* m_worldObject;
    EngineState m_engineState;
    bool m_overwriteEngineState;

    /* Return the euler angles needed to adjust 'up' */
    glm::vec3 rotateUpTo(const glm::vec3& up);
    glm::vec3 rotateUpAuto(const glm::quat& rotation);
};


