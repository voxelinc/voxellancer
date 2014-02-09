#include "aitask.h"


AiTask::AiTask(BoardComputer* boardComputer) :
    m_boardComputer(boardComputer)
{
}

BoardComputer* AiTask::boardComputer() {
    return m_boardComputer;
}

void AiTask::update(float deltaSec) {

}

bool AiTask::isInProgress() {
    return true;
}

