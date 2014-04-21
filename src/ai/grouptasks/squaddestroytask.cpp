#include "squaddestroytask.h"


SquadDestroyTask::SquadDestroyTask(Squad& squad, AiGroupTask* parent):
    AiGroupTask(squad, parent)
{

}

SquadDestroyTask::~SquadDestroyTask() = default;

void SquadDestroyTask::update(float deltaSec) {

}

