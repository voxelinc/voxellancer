#pragma once
/*
#include <vector>
#include <glm/glm.hpp>

#include "ai/aitask.h"

#include "utils/handle/handle.h"


class Ship;
class WorldObject;

class FightTask : public AiTask {
public:
    FightTask(BoardComputer* boardComputer, const std::vector<Handle<WorldObject>>& targets);

    virtual void update(float deltaSec);

    std::vector<Handle<WorldObject>>& targets();
    virtual void addTarget(const Handle<WorldObject>& targets);
    virtual void setTargets(const std::vector<Handle<WorldObject>>& targets);

    virtual bool isFinished();

protected:
    enum class State {
        IDLE,
        APPROACH,
        ENGAGE,
        EVADE
    };

    std::vector<Handle<WorldObject>> m_targets;
    WorldObject* m_primaryTarget;
    void updateTargets();
    void updateState();
    void setState(State newState);

    glm::vec3 findRandomEvasionPoint();
    float targetDistance();
    float pointDistance(glm::vec3 point);
    float angleToTarget();

    State m_state;
    bool m_stateChanged;
    float m_maxFireDistance, m_maxRocketDistance, m_minEnemyDistance;
    glm::vec3 m_positionBehindTarget;
};

*/