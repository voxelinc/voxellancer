#include "formationmembertask.h"

#include "worldobject/ship.h"
#include "ai/formationlogic.h"


FormationMemberTask::FormationMemberTask(Ship& ship, Ship* leader) :
    AiTask(ship.boardComputer()),
    m_ship(ship),
    m_flyTask(ship.boardComputer())
{
    if (leader) {
        m_ship.formationLogic()->joinFormation(leader);
    }
}

void FormationMemberTask::update(float deltaSec) {
    if (m_ship.formationLogic()->inFormation()) {
        m_flyTask.setTargetPoint(m_ship.formationLogic()->formationPosition(), m_ship.formationLogic()->formationUp());
        m_flyTask.update(deltaSec);
    }
}

