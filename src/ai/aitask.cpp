#include "aitask.h"


AiTask::AiTask(Ship& ship) :
    m_ship(ship)
{
}

void AiTask::update(float deltaSec) {

}

bool AiTask::isInProgress() {
    return true;
}