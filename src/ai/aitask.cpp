#include "aitask.h"


AiTask::AiTask(BoardComputer* boardComputer):
    m_boardComputer(boardComputer)
{
}

AiTask::~AiTask() = default;

BoardComputer* AiTask::boardComputer() {
    return m_boardComputer;
}

bool AiTask::isFinished() {
    return false;
}

