#include "defendareatask.h"

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
#include "factions/playerfaction.h"


DefendAreaTask::DefendAreaTask(Squad& squad, std::list<glm::vec3> points, float defendRange) :
AiGroupTask(squad),
m_points(points),
m_currentPoint(m_points.begin()),
m_fightTask(nullptr),
m_leaderFlyTask(nullptr),
m_defendRange(defendRange),
m_collisionFilter(new CollisionFilter(nullptr,0))
{
}

DefendAreaTask::~DefendAreaTask() = default;

void DefendAreaTask::update(float deltaSec) {
    if (m_squad.leader()) {
        if (isEnemyInRange()) {
            updateFight();
        } else {
            updatePatrol();
        }
        // update called by the leader himself
    }
}

void DefendAreaTask::onNewLeader(Ship* leader) {
    m_fightTask = std::make_shared<FightTask>(leader->boardComputer(), std::vector<Handle<WorldObject>>());
    m_leaderFlyTask = std::make_shared<FlyToTask>(leader->boardComputer());
    leader->character()->setTask(m_leaderFlyTask);
    m_collisionFilter = std::unique_ptr<CollisionFilter>(new CollisionFilter(leader, 0));
    m_collisionFilter->setCollideableWith(WorldObjectType::Ship, true);
}

void DefendAreaTask::onMemberJoin(Ship* member) {
    member->character()->setTask(std::make_shared<FormationMemberTask>(*member));
}

bool DefendAreaTask::isEnemyInRange() {
    m_enemies.clear();
    Faction* enemyFaction;
    Sphere sphere(m_squad.leader()->transform().position(), m_defendRange);
    WorldTreeQuery query(&(World::instance()->worldTree()), &sphere, nullptr, m_collisionFilter.get());
    for (WorldObject *worldObject : query.intersectingWorldObjects()) {
        Ship* ship = dynamic_cast<Ship*>(worldObject);
        if (ship) {
            enemyFaction = ship->character()->faction();
            if (enemyFaction && enemyFaction != m_squad.leader()->character()->faction() && enemyFaction->relationTo(m_squad.leader()->character()->faction())->type() == FactionRelationType::Enemy) {
                m_enemies.push_back(worldObject->handle());
            } else {
                continue;
            }
        }
    }
    return m_enemies.size() > 0;
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
    m_squad.leader()->character()->setTask(m_leaderFlyTask);
    for (Ship* ship : m_squad.members()) {
        ship->character()->setTask(std::make_shared<FormationMemberTask>(*ship));
    }
}

void DefendAreaTask::updateFight() {
    m_fightTask->setTargets(m_enemies);
    m_squad.leader()->character()->setTask(std::make_shared<FightTask>(m_squad.leader()->boardComputer(), m_enemies));
    for (Ship* ship : m_squad.members()) {
        ship->character()->setTask(std::make_shared<FightTask>(ship->boardComputer(), m_enemies));
    }
}