#pragma once

#include "worldobject/handle/handle.h"
#include "../basictask.h"
#include "worldobject/ship.h"
#include "utils/randfloat.h"


class FightTask : public BasicTask {

    enum State {
        IDLE,
        APPROACH,
        ENGAGE,
        EVADE
    };

public:
    FightTask(Ship& ship, std::list<Handle<WorldObject>> targets);

    virtual void update(float deltaSec);
    virtual void addTargets(std::list<Handle<WorldObject>> targets);
    virtual void setTargets(std::list<Handle<WorldObject>> targets);

    virtual bool isInProgress();

protected:
    std::list<Handle<WorldObject>> m_targets;
    WorldObject* m_primaryTarget;
    void updateTargets();
    void updateState();
    void setState(int newState);

    glm::vec3 findRandomEvasionPoint();
    float targetDistance();
    float pointDistance(glm::vec3 point);
    float angleToTarget();

    int m_state;
    bool m_stateChanged;
    float m_maxFireDistance, m_maxRocketDistance, m_minEnemyDistance;
    glm::vec3 m_positionBehindTarget;
};

