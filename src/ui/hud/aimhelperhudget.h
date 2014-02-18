#pragma once

#include <glm/glm.hpp>

#include "geometry/range.h"

#include "aimhelperhudgetvoxels.h"
#include "circularhudget.h"


class HUD;
class WorldObject;

/*
    Hudget drawn where player-bullets and target
    will collide i.e. not actually on the hud-sphere but
    in the world
*/
class AimHelperHudget: public CircularHudget {
public:
    AimHelperHudget(HUD* hud);

    /*
        The point the player should shoot at to hit
        his current enemy
    */
    const glm::vec3& targetPoint() const;

    virtual void update(float deltaSec) override;
    virtual void draw();


protected:
    AimHelperHudgetVoxels m_voxels;

    glm::vec3 m_targetPoint;
    glm::vec3 m_smoothTargetPoint;

    WorldObject* m_lastTargetWorldObject;
    bool m_lastVisible;

    Range m_distanceRange;

    void calculateTargetPoint(WorldObject* targetObject);
    void calculatedDirection();
};

