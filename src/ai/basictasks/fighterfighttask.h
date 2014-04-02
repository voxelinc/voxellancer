#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "ai/basictasks/fighttaskimplementation.h"

#include "utils/handle/handle.h"


class Ship;
class WorldObject;

/**
 *  FightTask for smaller and quicker ships
 */

class FighterFightTask : public FightTaskImplementation {
public:
    FighterFightTask(BoardComputer* boardComputer, const std::vector<Handle<WorldObject>>& targets);

    virtual void update(float deltaSec) override;

    virtual bool isFinished() override;

protected:
    enum class State {
        IDLE,
        APPROACH,
        ENGAGE,
        EVADE
    };

    void updateState();
    void setState(State newState);

    glm::vec3 findRandomEvasionPoint();
    float pointDistance(glm::vec3 point);
    float angleToTarget();

    State m_state;
    bool m_stateChanged;
    float m_maxFireDistance, m_maxRocketDistance, m_minEnemyDistance;
    glm::vec3 m_positionBehindTarget;
};

