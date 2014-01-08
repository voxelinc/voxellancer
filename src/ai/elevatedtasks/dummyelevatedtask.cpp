#include "dummyelevatedtask.h"

#include "ai/basictask.h"

DummyElevatedTask::DummyElevatedTask(Ship& ship, BasicTask* task) :
    ElevatedTask(ship),
    m_subtask(task)
{
}

void DummyElevatedTask::update(float deltaSec){
    m_subtask->update(deltaSec);
}