#pragma once
#include <set>

#include "glm/glm.hpp"

#include "ai/aitask.h"
#include "utils/handle/handle.h"


class BoardComputer;
class WorldObject;

class DirectSuicideTask : public AiTask {
public:
    DirectSuicideTask(BoardComputer* boardComputer, WorldObject* target);

    void setTarget(WorldObject* target);

    virtual void update(float deltaSec) override;


protected:
    Handle<WorldObject> m_target;
};

