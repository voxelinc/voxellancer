#include "formationmembertask.h"

#include "worldobject/ship.h"
#include "ai/squadlogic.h"

FormationMemberTask::FormationMemberTask(Ship& ship, Ship* leader) :
    AiTask(ship),
    m_flyTask(ship)
{
    if (leader) {
        ship.squadLogic()->joinFormation(leader);
    }
}

void FormationMemberTask::update(float deltaSec) {
    if (m_ship.squadLogic()->inFormation()) {
        m_flyTask.setTargetPoint(m_ship.squadLogic()->formationPosition(), m_ship.squadLogic()->formationUp());
        m_flyTask.update(deltaSec);
    }
}