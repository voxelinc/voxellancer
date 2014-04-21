#pragma once

#include "scripting/scriptable.h"

#include "utils/statemachine/state.h"
#include "utils/handle/handleowner.h"


class BoardComputer;
class WorldObject;

/**
 *  Basic unit for AI. A Ship's Character can always execute only one task.
 */
class AiTask : public State, public Scriptable, public HandleOwner {
public:
    AiTask(BoardComputer* boardComputer, AiTask* parent = nullptr);
    virtual ~AiTask();

    BoardComputer* boardComputer();
    AiTask* parent();

    virtual void update(float deltaSec);
    virtual bool isFinished();


protected:
    BoardComputer* m_boardComputer;
    AiTask* m_parent;
};

