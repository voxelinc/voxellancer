#pragma once

#include "ai/elevatedtask.h"


class Ship;
class BasicTask;

class DummyElevatedTask : public ElevatedTask
{
public:
    DummyElevatedTask(Ship& ship, BasicTask* task);

    virtual void update(float deltaSec);

protected:
    BasicTask* m_subtask;
};

