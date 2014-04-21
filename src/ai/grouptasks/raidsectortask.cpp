#include "raidsectortask.h"

#include "squadseektask.h"
#include "squaddestroytask.h"


RaidSectorTask::RaidSectorTask(Squad& squad, AiGroupTask* parent):
    AiGroupTask(squad, parent),
    m_seek(new SquadSeekTask(squad, this)),
    m_destroy(new SquadDestroyTask(squad, this))
{
    setInitialSubState(m_seek.get());
}

RaidSectorTask::~RaidSectorTask() = default;

void RaidSectorTask::update(float deltaSec) {
    AiGroupTask::update(deltaSec);
}

