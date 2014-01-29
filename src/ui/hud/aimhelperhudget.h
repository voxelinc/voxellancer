#pragma once

#include <glm/glm.hpp>

#include "geometry/range.h"

#include "aimhelperhudgetvoxels.h"
#include "circularhudget.h"


class HUD;

/*
    Hudget drawn where player-bullets and target
    will collide i.e. not actually on the hud-sphere but
    in the world
*/
class AimHelperHudget: public CircularHudget {
public:
    AimHelperHudget(HUD* hud);

    const glm::vec3& targetPoint() const;

    virtual void update(float deltaSec) override;
    virtual void draw();


protected:
    AimHelperHudgetVoxels m_voxels;
    glm::vec3 m_targetPoint;
    Range m_distanceRange;

    void calculateTargetPoint(WorldObject* targetObject);
    void calculatedDirection();
};

