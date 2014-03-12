#include "aitask.h"


AiTask::AiTask(BoardComputer* boardComputer):
    m_handle(Handle<AiTask>(this)),
    m_boardComputer(boardComputer)
{
}

AiTask::~AiTask() {
    m_handle.invalidate();
}

BoardComputer* AiTask::boardComputer() {
    return m_boardComputer;
}

void AiTask::update(float deltaSec) {

}

bool AiTask::isFinished() {
    return false;
}

Handle<AiTask>& AiTask::handle() {
    return m_handle;
}

