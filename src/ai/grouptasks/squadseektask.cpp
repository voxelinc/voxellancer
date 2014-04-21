#include "squadseektask.h"

#include <glow/logging.h>


SquadSeekTask::SquadSeekTask(Squad& squad, AiGroupTask* parent):
    AiGroupTask(squad, parent)
{

}

SquadSeekTask::~SquadSeekTask() = default;

void SquadSeekTask::update(float deltaSec) {

}

