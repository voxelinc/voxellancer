#pragma once

#include "rocket.h"


/**
 *   A special Rocket that detonates before reaching the target and spawns other rockets
 */
class SplitRocket: public Rocket {
public:
    SplitRocket();

    virtual void setTarget(WorldObject* targetObject) override;

    void setChildrenCount(int count);
    void setChildrenType(const std::string& type);

    /**
     * Distance to target within which the SplitRocketTask is allowed to split this
     */
    float splitDistance() const;
    void setSplitDistance(float splitDistance);

    float splitAngle() const;
    void setSplitAngle(float splitAngle);

    void split();


protected:
    int m_childrenCount;
    std::string m_childrenType;
    float m_splitDistance;
    float m_splitAngle;

    void spawnChildren();
    virtual void spawnExplosion() override;
};

