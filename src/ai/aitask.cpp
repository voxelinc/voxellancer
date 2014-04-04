#include "aitask.h"


AiTask::AiTask(BoardComputer* boardComputer):
    m_boardComputer(boardComputer)
{
}

AiTask::~AiTask() = default;

BoardComputer* AiTask::boardComputer() {
    return m_boardComputer;
}

void AiTask::update(float deltaSec) {

}

bool AiTask::isFinished() {
    return false;
}

