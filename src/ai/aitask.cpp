#include "aitask.h"


AiTask::AiTask(BoardComputer* boardComputer):
    m_handle(Handle<AiTask>(this)),
    m_boardComputer(boardComputer)
{
}

AiTask::~AiTask() {
    m_handle.invalidate();
}

ScriptableType AiTask::scriptableType() const {
    return ScriptableType::AiTask;
}

BoardComputer* AiTask::boardComputer() {
    return m_boardComputer;
}

void AiTask::update(float deltaSec) {

}

bool AiTask::isInProgress() {
    return true;
}

Handle<AiTask>& AiTask::handle() {
    return m_handle;
}

