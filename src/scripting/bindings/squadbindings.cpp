#include "squadbindings.h"

#include <memory>

#include "ai/squad.h"
#include "ai/squadlogic.h"
#include "ai/grouptasks/patrolwaypointstask.h"
#include "ai/grouptasks/defendareatask.h"

#include "scripting/scriptengine.h"
#include "scripting/elematelua/luawrapper.h"

#include "worldobject/ship.h"

SquadBindings::SquadBindings(GamePlayScript& script):
    Bindings(script)
{

}

void SquadBindings::initialize() {
    m_lua.Register("createSquad", this, &SquadBindings::apiCreateSquad);
    m_lua.Register("joinSquad", this, &SquadBindings::apiJoinSquad);
    m_lua.Register("createPatrolWaypointsTask", this, &SquadBindings::apiCreatePatrolWaypointsTask);
    m_lua.Register("addPatrolwWaypointPoint", this, &SquadBindings::apiAddPatrolwWaypointPoint);
    m_lua.Register("createDefendAreaTask", this, &SquadBindings::apiCreateDefendAreaTask);
    m_lua.Register("addDefendAreaPoint", this, &SquadBindings::apiAddDefendAreaPoint);
}

apikey SquadBindings::apiCreateSquad(apikey leader) {
    Ship* ship = m_scriptEngine.get<Ship>(leader);

    if (!ship) { return -1; }

    auto squad = std::make_shared<Squad>();
    m_scriptEngine.registerScriptable(squad.get());

    ship->squadLogic()->joinSquad(squad);

    return squad->scriptKey();   
}

int SquadBindings::apiJoinSquad(apikey squadKey, apikey shipKey) {
    Squad* squad = m_scriptEngine.get<Squad>(squadKey);
    if (!squad) { return -1; }

    Ship* ship = m_scriptEngine.get<Ship>(shipKey);
    if (!ship) { return -1; }

    ship->squadLogic()->joinSquadOf(squad->leader());
    return 0;
}

int SquadBindings::apiCreatePatrolWaypointsTask(apikey squadKey) {
    Squad* squad = m_scriptEngine.get<Squad>(squadKey);
    
    if (!squad) { return -1; }
    
    auto task = std::make_shared<PatrolWaypointsTask>(*squad);
    m_scriptEngine.registerScriptable(task.get());

    squad->setTask(task);

    return task->scriptKey();
}

int SquadBindings::apiAddPatrolwWaypointPoint(apikey taskKey, const glm::vec3& point) {
    PatrolWaypointsTask* task = m_scriptEngine.get<PatrolWaypointsTask>(taskKey);

    if (!task) { return -1; }

    task->appendWaypoint(point);
    return 0;
}

int SquadBindings::apiCreateDefendAreaTask(apikey squadKey, const glm::vec3& point, float range) {
    Squad* squad = m_scriptEngine.get<Squad>(squadKey);

    if (!squad) { return -1; }

    auto task = std::shared_ptr<DefendAreaTask>(new DefendAreaTask(*squad, { point }, range));
    m_scriptEngine.registerScriptable(task.get());

    squad->setTask(task);

    return task->scriptKey();
}

int SquadBindings::apiAddDefendAreaPoint(apikey taskKey, const glm::vec3& point) {
    DefendAreaTask* task = m_scriptEngine.get<DefendAreaTask>(taskKey);

    if (!task) { return -1; }

    task->addPoint(point);
    return 0;
}



