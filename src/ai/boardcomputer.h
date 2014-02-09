#pragma once

#include <vector>
#include <list>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "worldobject/components/enginestate.h"
#include "worldobject/handle/handle.h"


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

    void rotateUpTo(const glm::vec3& up);
    void rotateUpAuto(const glm::quat& rotation);
};


