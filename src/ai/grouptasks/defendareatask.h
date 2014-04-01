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
    ~DefendAreaTask();

    void addPoint(const glm::vec3& point);
    
    const std::list<glm::vec3>& points();
    float range();

    virtual void update(float deltaSec) override;

protected:
    virtual void onNewLeader(Ship* leader) override;
    virtual void onMemberJoin(Ship* member) override;
    void setPatrol();
    void setFight();
    void updatePatrol();
    void updateFight();

    bool isEnemyInRange();

    std::unique_ptr<CollisionFilter> m_collisionFilter;
    std::shared_ptr<FlyToTask> m_leaderFlyTask;
    std::shared_ptr<FightTask> m_leaderFightTask;
    std::list<glm::vec3> m_points;
    std::list<glm::vec3>::iterator m_currentPoint;
    std::vector<Handle<WorldObject>> m_enemies;

    float m_defendRange;
    bool m_fighting;
};

