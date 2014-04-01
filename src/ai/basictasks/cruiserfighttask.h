#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "ai/basictasks/fighttaskimplementation.h"

#include "utils/handle/handle.h"


class Ship;
class WorldObject;

/**
 *  FightTask for bigger ships and captials
 */

class CruiserFightTask : public FightTaskImplementation {
public:
    CruiserFightTask(BoardComputer* boardComputer, const std::vector<Handle<WorldObject>>& targets);

    virtual void update(float deltaSec) override;

    virtual bool isFinished() override;

protected:
    enum class State {
        IDLE,
        ENGAGE
    };

    WorldObject* m_primaryTarget;
    void updateTargets();
    void updateState();
    void setState(State newState);

    float targetDistance();
    float anyTargetDistance();
    float angleToTarget();

    State m_state;
    bool m_stateChanged;
    float m_maxFireDistance, m_maxRocketDistance, m_minEnemyDistance;
};
