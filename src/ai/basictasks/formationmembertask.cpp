#include "formationmembertask.h"

#include "worldobject/ship.h"
#include "ai/formationlogic.h"

FormationMemberTask::FormationMemberTask(Ship& ship, Ship* leader) :
    AiTask(ship),
    m_flyTask(ship)
{
    ship.formationLogic()->joinFormation(leader);
}

void FormationMemberTask::update(float deltaSec) {
    m_flyTask.setTargetPoint(m_ship.formationLogic()->formationPosition());
    m_flyTask.update(deltaSec);
}