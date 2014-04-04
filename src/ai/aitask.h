#pragma once

#include "scripting/scriptable.h"

#include "utils/handle/handle.h"
#include "utils/handle/handleowner.h"


class BoardComputer;
class WorldObject;

/**
 *  Basic unit for AI. A Ship's Character can always execute only one task.
 */

class AiTask : public Scriptable, public HandleOwner {
public:
    AiTask(BoardComputer* boardComputer);
    virtual ~AiTask();

    BoardComputer* boardComputer();

    virtual void update(float deltaSec);
    virtual bool isFinished();


protected:
    BoardComputer* m_boardComputer;
};

