#pragma once

#include "ai/aigrouptask.h"

#include <list>

#include "glm/glm.hpp"

#include "ai/basictasks/flytotask.h"
#include "ai/basictasks/fighttask.h"

class CollisionFilter;
class Squad;
class Sphere;

class DefendAreaTask : public AiGroupTask {
public:
    DefendAreaTask(Squad& squad, std::list<glm::vec3> points, float defendRange);

    virtual void update(float deltaSec) override;

protected:
    virtual void onNewLeader(Ship* leader) override;
    virtual void onMemberJoin(Ship* member) override;
    void updatePatrol();
    void updateFight();

    bool isEnemyInRange();

    std::shared_ptr<FlyToTask> m_leaderFlyTask;
    std::shared_ptr<FightTask> m_fightTask;
    std::list<glm::vec3> m_points;
    std::list<glm::vec3>::iterator m_currentPoint;
    std::vector<Handle<WorldObject>> m_enemies;

    std::unique_ptr<CollisionFilter> m_shipFilter;
    float m_defendRange;
};

