#pragma once

#include "scripting/scriptable.h"

#include "utils/handle/handle.h"


class BoardComputer;
class WorldObject;

/**
 *  Basic unit for AI. A Ship's Character can always execute only one task.
 */

class AiTask : public Scriptable {
public:
    AiTask(BoardComputer* boardComputer);
    virtual ~AiTask();

    BoardComputer* boardComputer();

    virtual void update(float deltaSec);
    virtual bool isFinished();

    Handle<AiTask>& handle();


protected:
    Handle<AiTask> m_handle;
    BoardComputer* m_boardComputer;
};

