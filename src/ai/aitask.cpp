#include "aitask.h"


AiTask::AiTask(BoardComputer* boardComputer, AiTask* parent):
    State(parent),
    m_boardComputer(boardComputer),
    m_parent(parent)
{
}

AiTask::~AiTask() = default;

BoardComputer* AiTask::boardComputer() {
    return m_boardComputer;
}

AiTask* AiTask::parent() {
    return m_parent;
}

void AiTask::update(float deltaSec) {
    State::update(deltaSec);
}

bool AiTask::isFinished() {
    return false;
}

