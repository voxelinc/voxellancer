#include "defendareatask.h"

#include <memory>

#include "worldobject/ship.h"
#include "ai/squadlogic.h"
#include "ai/squad.h"
#include "ai/character.h"
#include "ai/basictasks/formationmembertask.h"
#include "voxel/voxelclusterbounds.h"
#include "worldtree/worldtreequery.h"
#include "geometry/sphere.h"
#include "world/world.h"
#include "worldtree/worldtree.h"
#include "collision/collisionfilter.h"
#include "factions/faction.h"
#include "factions/factionmatrix.h"
#include "factions/factionrelation.h"


DefendAreaTask::DefendAreaTask(Squad& squad, std::list<glm::vec3> points, float defendRange) :
    AiGroupTask(squad),
    m_points(points),
    m_currentPoint(m_points.begin()),
    m_leaderFightTask(nullptr),
    m_leaderFlyTask(nullptr),
    m_defendRange(defendRange),
    m_collisionFilter(new CollisionFilter(nullptr,0)),
    m_fighting(false)
{
}

DefendAreaTask::~DefendAreaTask() = default;

void DefendAreaTask::update(float deltaSec) {
    if (m_squad.leader()) {
        if (m_fighting) {
            if (isEnemyInRange()) {
                updateFight();
            } else {
                setPatrol();
            }
        } else {
            if (isEnemyInRange()) {
                setFight();
            } else {
                updatePatrol();
            }
        }

        // update called by the leader himself
    }
}

void DefendAreaTask::onNewLeader(Ship* leader) {
    m_leaderFightTask = std::make_shared<FightTask>(leader->boardComputer(), std::vector<Handle<WorldObject>>());
    m_leaderFlyTask = std::make_shared<FlyToTask>(leader->boardComputer());
    leader->character()->setTask(m_leaderFlyTask);
    m_collisionFilter = std::unique_ptr<CollisionFilter>(new CollisionFilter(leader, 0));
    m_collisionFilter->setCollideableWith(WorldObjectType::Ship, true);
}

void DefendAreaTask::onMemberJoin(Ship* member) {
    if (m_fighting) {
        setFight();
    } else {
        setPatrol();
    }
}

bool DefendAreaTask::isEnemyInRange() {
    m_enemies.clear();
    Sphere sphere(m_squad.leader()->transform().position(), m_defendRange);
    WorldTreeQuery query(&(World::instance()->worldTree()), &sphere, nullptr, m_collisionFilter.get());
    for (WorldObject *worldObject : query.intersectingWorldObjects()) {
        Ship* ship = dynamic_cast<Ship*>(worldObject);
        if (ship) {
            Faction& enemyFaction = ship->character()->faction();
            if (enemyFaction.relationTo(m_squad.leader()->character()->faction()).type() == FactionRelationType::Enemy) {
                m_enemies.push_back(worldObject->handle<WorldObject>());
            } else {
                continue;
            }
        }
    }
    return m_enemies.size() > 0;
}

void DefendAreaTask::setPatrol() {
    updatePatrol();
    m_squad.leader()->character()->setTask(m_leaderFlyTask);
    for (Ship* ship : m_squad.followers()) {
        ship->character()->setTask(std::make_shared<FormationMemberTask>(*ship));
    }
    m_fighting = false;
}

void DefendAreaTask::setFight() {
    m_leaderFightTask->setTargets(m_enemies);
    m_squad.leader()->character()->setTask(m_leaderFightTask);
    for (Ship* ship : m_squad.followers()) {
        ship->character()->setTask(std::make_shared<FightTask>(ship->boardComputer(), m_enemies));
    }
    m_fighting = true;
}

void DefendAreaTask::updatePatrol() {
    float distance = glm::length(*m_currentPoint - m_squad.leader()->transform().position());
    if (distance < m_squad.leader()->bounds().sphere().radius()) {
        m_currentPoint++;
        if (m_currentPoint == m_points.end()) {
            m_currentPoint = m_points.begin();
        }
    }
    m_leaderFlyTask->setTargetPoint(*m_currentPoint);
}

void DefendAreaTask::updateFight() {
    assert(m_fighting); // they already have FightTasks
    for (Ship* ship : m_squad.members()) {
        FightTask* task = dynamic_cast<FightTask*>(ship->character()->task().get());
        assert(task);
        if (task) {
            task->setTargets(m_enemies);
        }
    }
}

void DefendAreaTask::addPoint(const glm::vec3& point) {
    m_points.push_back(point);
}

const std::list<glm::vec3>& DefendAreaTask::points() {
    return m_points;
}

float DefendAreaTask::range() {
    return m_defendRange;
}
