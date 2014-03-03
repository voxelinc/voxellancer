#pragma once

#include "scripting/scriptable.h"

#include "utils/handle/handle.h"


class BoardComputer;
class WorldObject;

class AiTask : public Scriptable {
public:
    AiTask(BoardComputer* boardComputer);
    virtual ~AiTask();

    virtual ScriptableType scriptableType() const override;

    BoardComputer* boardComputer();

    virtual void update(float deltaSec);
    virtual bool isInProgress();

    Handle<AiTask>& handle();


protected:
    Handle<AiTask> m_handle;
    BoardComputer* m_boardComputer;
};

