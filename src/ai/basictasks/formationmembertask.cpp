#include "formationmembertask.h"

#include "worldobject/ship.h"
#include "ai/squadlogic.h"


FormationMemberTask::FormationMemberTask(Ship& ship) :
    AiTask(ship.boardComputer()),
    m_ship(ship),
    m_flyTask(ship.boardComputer())
{

}

void FormationMemberTask::update(float deltaSec) {
    if (m_ship.squadLogic()->inSquad()) {
        m_flyTask.setTargetPoint(m_ship.squadLogic()->formationPosition(), m_ship.squadLogic()->formationUp());
        m_flyTask.update(deltaSec);
    }
}

