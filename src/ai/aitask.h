#pragma once

#include "scripting/scriptable.h"

#include "utils/handle/handle.h"
#include "utils/statemachine/state.h"


class BoardComputer;
class WorldObject;

/**
 *  Basic unit for AI. A Ship's Character can always execute only one task.
 */
class AiTask : public State, public Scriptable {
public:
    AiTask(BoardComputer* boardComputer, AiTask* parent = nullptr);
    virtual ~AiTask();

    BoardComputer* boardComputer();
    AiTask* parent();

    virtual void update(float deltaSec) = 0;
    virtual bool isFinished();

    Handle<AiTask>& handle();


protected:
    Handle<AiTask> m_handle;
    BoardComputer* m_boardComputer;
    AiTask* m_parent;
};

