#pragma once

#include "worldobject/worldobjecthandle.h"
#include "../basictask.h"
#include "worldobject/ship.h"

class Fight : public BasicTask {
public:
    Fight(Ship& ship, std::list<std::shared_ptr<WorldObjectHandle>> targets);

    virtual void update(float deltaSec);
    virtual void addTargets(std::list<std::shared_ptr<WorldObjectHandle>> targets);
    virtual void setTargets(std::list<std::shared_ptr<WorldObjectHandle>> targets);

    virtual bool isInProgress();

protected:
    std::list<std::shared_ptr<WorldObjectHandle>> m_targets;
    WorldObject* m_primaryTarget;
    void updateTargets();
};

