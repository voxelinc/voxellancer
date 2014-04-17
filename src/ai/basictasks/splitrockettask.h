#pragma once

#include "directsuicidetask.h"


class SplitRocket;
class BoardComputer;
class WorldObject;

class SplitRocketTask : public DirectSuicideTask {
public:
    SplitRocketTask(SplitRocket* rocket, BoardComputer* boardComputer, WorldObject* target);

    virtual void update(float deltaSec) override;


protected:
    SplitRocket* m_rocket;
    float m_flytime;

};

