#pragma once

#include "ai/aitask.h"

#include <list>

#include "glm/glm.hpp"

#include "ai/basictasks/flytotask.h"


class Ship;

class FormationMemberTask : public AiTask {
public:
    FormationMemberTask(Ship& ship);

    virtual void update(float deltaSec) override;


protected:
    FlyToTask m_flyTask;
};

