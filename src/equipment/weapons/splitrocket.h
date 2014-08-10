#pragma once

#include "rocket.h"


/**
 * A special Rocket that detonates before reaching the target and spawns other rockets
 */
class SplitRocket: public Rocket {
public:
    SplitRocket();

    virtual void setTarget(WorldObject* targetObject) override;

    void setChildrenCount(int count);
    void setChildrenType(const std::string& type);

    /**
     * Additional speed the children receive when splitting
     */
    float childrenSpeedBoost() const;
    void setChildrenSpeedBoost(float childrenSpeedBoost);

    float childrenSpeedBoostRandomization() const;
    void setChildrenSpeedBoostRandomization(float childrenSpeedBoostRandomization);

    /**
     * Distance to target within which the SplitRocketTask is allowed to split this
     */
    float splitDistance() const;
    void setSplitDistance(float splitDistance);

    /**
     * Maximum difference between rocket-orientation and direction to target in which
     * a split is allowed
     */
    float splitDirectionTolerance() const;
    void setSplitDirectionTolerance(float splitDirectionTolerance);

    /**
     * Angle from fly-direction to direction of the spawned children
     */
    float splitAngle() const;
    void setSplitAngle(float splitAngle);

    float splitAngleRandomization() const;
    void setSplitAngleRandomization(float splitAngleRandomization);

    float minFlytimeBeforeSplit() const;
    void setMinFlytimeBeforeSplit(float minFlytimeBeforeSplit);

    void split();


protected:
    int m_childrenCount;
    std::string m_childrenType;
    float m_childrenSpeedBoost;
    float m_childrenSpeedBoostRandomization;
    float m_splitDistance;
    float m_splitDirectionTolerance;
    float m_splitAngle;
    float m_splitAngleRandomization;
    float m_minFlytimeBeforeSplit;

    void spawnChildren();
    void setChildSpeed(WorldObject* child, const glm::quat& launchOrientation);
    virtual void spawnExplosion() override;
};

