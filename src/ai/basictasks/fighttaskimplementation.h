#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "ai/aitask.h"
#include "utils/handle/handle.h"


class Ship;
class WorldObject;
class ComponentsInfo;

/**
 *  Base Class for all FightTask variants, e.g. for FighterFightTask
 */
class FightTaskImplementation : public AiTask {
public:
    FightTaskImplementation(BoardComputer* boardComputer, const std::vector<Handle<WorldObject>>& targets);

    virtual void update(float deltaSec) override = 0;

    std::vector<Handle<WorldObject>>& targets();
    virtual void addTarget(const Handle<WorldObject>& targets);
    virtual void setTargets(const std::vector<Handle<WorldObject>>& targets);

    virtual bool isFinished() override = 0;

protected:
    std::vector<Handle<WorldObject>> m_targets;
    WorldObject* m_primaryTarget;

    void updateTargets();
    float targetDistance();

    const ComponentsInfo& componentsInfo();
};

